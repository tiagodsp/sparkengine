#include "sparkengine.PCH.h"
#include "OpenGLTexture2D.h"

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Spark
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
        : m_FilePath(filepath)
    {
        int32 width, height, channels;
        stbi_uc* data = stbi_load(m_FilePath.c_str(), &width, &height, &channels, 0); // Load image from file
        CORE_ASSERT(data, "Failed to load image!");
        
        // Successuful load, then start to configure class based on data;
        m_Width = width;
        m_Height = height;

        GLenum textureFormat = 0, dataFormat = 0;
        if(channels == 3)
        {
            textureFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        else if(channels == 4)
        {
            textureFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }


        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        //glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        //glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

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
}
