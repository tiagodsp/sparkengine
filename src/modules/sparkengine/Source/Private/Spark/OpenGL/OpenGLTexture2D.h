#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Renderer/Texture.h"


namespace Spark
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32 Width, uint32 Height, TextureFormat TextureFormat);
        OpenGLTexture2D(const std::string& filepath);
        virtual ~OpenGLTexture2D();

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
        uint32 m_Channels;
        TextureFormat m_TextureFormat;
        PixelFormat m_PixelFormat;
    };

}