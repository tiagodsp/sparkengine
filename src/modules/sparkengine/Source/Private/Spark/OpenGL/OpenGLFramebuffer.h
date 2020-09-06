#pragma once
#include "Spark/Core/CoreTypes.h"
#include "Spark/Renderer/Framebuffer.h"

namespace Spark
{
    class OpenGLFramebuffer : public IFramebuffer
    {
    private:
        FramebufferProperties m_Properties;
        uint32 m_RendererID;
        uint32 m_ColorAttachmentRendererID;
        uint32 m_DepthAttachmentRendererID;

    public:
        OpenGLFramebuffer(const FramebufferProperties& Properties);
        ~OpenGLFramebuffer();

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void Invalidate() override;
        virtual uint32 GetRendererID() override { return m_RendererID; }
        virtual uint32 GetColorAttachmentRendererID() override { return m_ColorAttachmentRendererID; }
        virtual uint32 GetDepthAttachmentRendererID() override { return m_DepthAttachmentRendererID; }
        virtual const FramebufferProperties &GetProperties() const override {return m_Properties; }
        virtual void SetProperties(const FramebufferProperties& Properties) override;
    };

} // namespace Spark