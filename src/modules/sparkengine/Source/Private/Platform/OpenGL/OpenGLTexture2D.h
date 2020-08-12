#pragma once

#include "Spark/Renderer/Texture.h"

namespace Spark
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& filepath);
        virtual ~OpenGLTexture2D();

        // Texture overrides --------------
        virtual uint32 GetWidth() const override { return m_Width; }
        virtual uint32 GetHeight() const override { return m_Height; }
        virtual void Bind() const override;
    private:
        std::string m_FilePath;
        uint32 m_Width, m_Height;
        uint32 m_Renderer2D;        
    };



}