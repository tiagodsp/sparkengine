#include "sparkengine.PCH.h"
#include "MetalTexture2D.h"

#include "Spark/Renderer/Renderer.h"
#include "Spark/Metal/MetalPlatformRendererAPI.h"
#include <Metal/Metal.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Spark
{
    
    static MTLPixelFormat GetMetalInternalFormatPerTexFormat(Texture::TextureFormat TextureFormat)
    {
        switch (TextureFormat)
        {
        case Texture::TextureFormat::NONE    : CORE_ASSERT(false, "Texture Format not supported!"); return MTLPixelFormatInvalid;
        case Texture::TextureFormat::RGB8    : return MTLPixelFormatRGBA8Uint;
        case Texture::TextureFormat::RGBA8   : return MTLPixelFormatRGBA8Uint;
        case Texture::TextureFormat::RGB32   : return MTLPixelFormatRGBA32Uint;
        case Texture::TextureFormat::RGBA32  : return MTLPixelFormatRGBA32Uint;
        case Texture::TextureFormat::BGR8    : return MTLPixelFormatBGRA8Unorm;
        case Texture::TextureFormat::BGRA8   : return MTLPixelFormatBGRA8Unorm;
        case Texture::TextureFormat::BGR32   :
        case Texture::TextureFormat::BGRA32  :
        // TODO: Support compressed pixel formats.
        //case Texture::TextureFormat::DXT     : return GL_NONE;
        //case Texture::TextureFormat::DXT5    : return GL_NONE;
        //case Texture::TextureFormat::ETC     : return GL_NONE;
        //case Texture::TextureFormat::ETC2    : return GL_NONE;
        default:
            CORE_ASSERT(false, "Texture Format not supported!");
            return MTLPixelFormatInvalid;
        }
    }

    MetalTexture2D::MetalTexture2D(uint32 Width, uint32 Height, TextureFormat TextureFormat)
    {
        m_Width = Width;
        m_Height = Height;
        m_Channels = 4;

        m_TextureFormat = TextureFormat;
    }

    MetalTexture2D::MetalTexture2D(const std::string& filepath)
        : m_FilePath(filepath)
    {
        int32 width, height, channels;
        stbi_uc* data = stbi_load(m_FilePath.c_str(), &width, &height, &channels, 0); // Load image from file
        CORE_ASSERT(data, "Failed to load image!");
        
        // Successuful load, then start to configure class based on data;
        m_Width = width;
        m_Height = height;
        m_Channels = channels;

        if(channels == 3)
        {
            m_TextureFormat = TextureFormat::RGB8;
            m_PixelFormat = PixelFormat::RGB;
        }
        else if(channels == 4)
        {
            m_TextureFormat = TextureFormat::RGBA8;
            m_PixelFormat = PixelFormat::RGBA;
        }
        
        SetTextureData(data, m_Width * m_Height * m_Channels, m_PixelFormat);
        stbi_image_free(data);

    }

    MetalTexture2D::~MetalTexture2D()
    {
        [m_Texture release];
    }

    void MetalTexture2D::Bind(uint32 slot) const
    {
        Ref<MetalPlatformRendererAPI> metalApi = std::static_pointer_cast<MetalPlatformRendererAPI>(Renderer::GetLowLevelAPI());
        [metalApi->m_CommandEncoder setFragmentTexture:m_Texture atIndex:slot];
    }

    void MetalTexture2D::Unbind() const
    {
        // Implement Unbind...
    }

    void MetalTexture2D::SetTextureData(const void* Data, size_t Size, PixelFormat PixelFormat)
    {
        m_PixelFormat = PixelFormat;
        
        Ref<MetalPlatformRendererAPI> metalApi = std::static_pointer_cast<MetalPlatformRendererAPI>(Renderer::GetLowLevelAPI());
        
        // Create texture descriptor -------------
        MTLTextureDescriptor* textureDescriptor = [[MTLTextureDescriptor alloc] init];
        textureDescriptor.width = m_Width;
        textureDescriptor.height = m_Height;
        textureDescriptor.pixelFormat = GetMetalInternalFormatPerTexFormat(m_TextureFormat);
        textureDescriptor.mipmapLevelCount = 1;
        
        m_Texture = [metalApi->m_Device newTextureWithDescriptor:textureDescriptor];
        
        MTLRegion region = {
            { 0, 0, 0 },                   // MTLOrigin
            {m_Width, m_Height, 1} // MTLSize
        };
        
        [m_Texture replaceRegion:region mipmapLevel:0 withBytes:Data bytesPerRow:m_Width * sizeof(uint32)];
    }

}
