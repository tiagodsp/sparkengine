#include "Spark/OpenGL/OpenGLFramebuffer.h"
#include "glad/glad.h"

namespace Spark
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferProperties &Properties)
        : m_Properties(Properties)
    {
        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteTextures(1, &m_ColorAttachmentRendererID);
        glDeleteTextures(1, &m_DepthAttachmentRendererID);
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Invalidate()
    {

        // Create color attachment:
        glGenTextures(1, &m_ColorAttachmentRendererID);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentRendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Properties.Size.x, m_Properties.Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glBindTexture(GL_TEXTURE_2D, 0);

        
        // Create depth attachment
        glGenTextures(1, &m_DepthAttachmentRendererID);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachmentRendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Properties.Size.x, m_Properties.Size.y, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindTexture(GL_TEXTURE_2D, 0);
        
        
        // Create Framebuffer:
        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentRendererID, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachmentRendererID, 0);
        CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void OpenGLFramebuffer::SetProperties(const FramebufferProperties &Properties)
    {
        m_Properties = Properties;
        Invalidate();
    }
} // namespace Spark