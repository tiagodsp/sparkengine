#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Renderer/Texture.h"
#include <Metal/Metal.h>


namespace Spark
{
    class MetalTexture2D : public Texture2D
    {
    public:
        MetalTexture2D(uint32 Width, uint32 Height, TextureFormat TextureFormat);
        MetalTexture2D(const std::string& filepath);
        virtual ~MetalTexture2D();

        // Texture overrides --------------
        virtual uint32 GetWidth() const override { return m_Width; }
        virtual uint32 GetHeight() const override { return m_Height; }
        virtual void Bind(uint32 slot = 0) const override;
        virtual void Unbind() const override;
        virtual uint32 GetRendererID() const override { return m_RendererID; };
        virtual void SetTextureData(const void* Data, size_t Size, PixelFormat PixelFormat) override;
    private:
        std::string m_FilePath;
        uint32 m_Width, m_Height;
        uint32 m_RendererID;
        id<MTLTexture> m_Texture;
        uint32 m_Channels;
        TextureFormat m_TextureFormat;
        PixelFormat m_PixelFormat;
    };

}
