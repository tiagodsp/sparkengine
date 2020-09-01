#include "sparkengine.PCH.h"
#include "OpenGLTexture2D.h"

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Spark
{
    
    static GLenum GetGLInternalFormatPerTexFormat(Texture::TextureFormat TextureFormat)
    {
        switch (TextureFormat)
        {
        case Texture::TextureFormat::NONE    : return GL_NONE;
        case Texture::TextureFormat::RGB8    : return GL_RGB8;
        case Texture::TextureFormat::RGBA8   : return GL_RGBA8;
        case Texture::TextureFormat::RGB32   : return GL_BGR_INTEGER;
        case Texture::TextureFormat::RGBA32  : return GL_BGRA_INTEGER;
        case Texture::TextureFormat::BGR8    : return GL_BGR;
        case Texture::TextureFormat::BGRA8   : return GL_BGRA;
        case Texture::TextureFormat::BGR32   : return GL_BGR_INTEGER;
        case Texture::TextureFormat::BGRA32  : return GL_BGRA_INTEGER;
        // TODO: Support compressed pixel formats.
        //case Texture::TextureFormat::DXT     : return GL_NONE;
        //case Texture::TextureFormat::DXT5    : return GL_NONE;
        //case Texture::TextureFormat::ETC     : return GL_NONE;
        //case Texture::TextureFormat::ETC2    : return GL_NONE;
        default:
            CORE_ASSERT(false, "Texture Format not supported!");
            return GL_NONE;
        }
    }
    
    static GLenum GetGLDataFormatPerPixelFormat(Texture::PixelFormat PixelFormat)
    {
        switch (PixelFormat)
        {
        case Texture::PixelFormat::NONE   : return GL_NONE;
        case Texture::PixelFormat::RGB    : return GL_RGB;
        case Texture::PixelFormat::RGBA   : return GL_RGBA;
        case Texture::PixelFormat::BGR    : return GL_BGR;
        case Texture::PixelFormat::BGRA   : return GL_BGRA;
        // TODO: Support compressed texture formats.
        //case Texture::TextureFormat::DXT    : return GL_NONE;
        //case Texture::TextureFormat::DXT5   : return GL_NONE;
        //case Texture::TextureFormat::ETC    : return GL_NONE;
        //case Texture::TextureFormat::ETC2   : return GL_NONE;
        case Texture::PixelFormat::RED    : return GL_RED;
        case Texture::PixelFormat::GREEN  : return GL_GREEN;
        case Texture::PixelFormat::BLUE   : return GL_BLUE;
        default:
            CORE_ASSERT(false, "Pixel Format not supported!");
            return GL_NONE;
        }
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32 Width, uint32 Height, TextureFormat TextureFormat)
    {
        m_Width = Width;
        m_Height = Height;
        m_Channels = 4;

        m_TextureFormat = TextureFormat;

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
        : m_FilePath(filepath)
    {
        int32 width, height, channels;
        stbi_uc* data = stbi_load(m_FilePath.c_str(), &width, &height, &channels, 0); // Load image from file
        CORE_ASSERT(data, "Failed to load image!");
        
        // Successuful load, then start to configure class based on data;
        m_Width = width;
        m_Height = height;
        m_Channels = channels;

        GLenum internalFormat = 0, dataFormat = 0;
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

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        
        SetTextureData(data, m_Width * m_Height * m_Channels, m_PixelFormat);
        stbi_image_free(data);

    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32 slot) const
    {
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void OpenGLTexture2D::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture2D::SetTextureData(const void* Data, size_t Size, PixelFormat PixelFormat)
    {
        m_PixelFormat = PixelFormat;
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GetGLInternalFormatPerTexFormat(m_TextureFormat),
            m_Width,
            m_Height,
            0,
            GetGLDataFormatPerPixelFormat(m_PixelFormat),
            GL_UNSIGNED_BYTE,
            Data
        );
    }

}
