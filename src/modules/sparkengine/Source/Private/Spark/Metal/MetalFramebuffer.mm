#include "Spark/Metal/MetalFramebuffer.h"
#include <Metal/Metal.h>
#include "Spark/Renderer/Renderer.h"
#include "Spark/Metal/MetalGraphicsContext.h"
namespace Spark
{
    MetalFramebuffer::MetalFramebuffer(const FramebufferProperties &Properties)
        : m_Properties(Properties)
    {
        Invalidate();
    }

    MetalFramebuffer::~MetalFramebuffer()
    {
        [m_ColorTexture release];
        [m_DepthTexture release];
        [m_RenderPassDescriptor release];
    }

    void MetalFramebuffer::Bind()
    {
        Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
        m_CommandBuffer = [context->m_CommandQueue commandBuffer];
        context->m_CommandEncoder = [m_CommandBuffer renderCommandEncoderWithDescriptor:m_RenderPassDescriptor];
    }

    void MetalFramebuffer::Unbind()
    {
        // Implement Unbind...
    }

    void MetalFramebuffer::Invalidate()
    {
        if(m_RenderPassDescriptor)
        {
            [m_ColorTexture release];
            [m_DepthTexture release];
            [m_RenderPassDescriptor release];
        }
        
        Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
        
        // Color attachment texture -------------
        MTLTextureDescriptor* colorTextureDescriptor = [[MTLTextureDescriptor alloc] init];
        colorTextureDescriptor.width = m_Properties.Size.x;
        colorTextureDescriptor.height = m_Properties.Size.y;
        colorTextureDescriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
        colorTextureDescriptor.mipmapLevelCount = 1;
        colorTextureDescriptor.usage = MTLTextureUsageRenderTarget;
        
        m_ColorTexture = [context->m_Device newTextureWithDescriptor:colorTextureDescriptor];
        
        // Depth attachment texture --------------
        MTLTextureDescriptor* depthTextureDescriptor = [[MTLTextureDescriptor alloc] init];
        depthTextureDescriptor.width = m_Properties.Size.x;
        depthTextureDescriptor.height = m_Properties.Size.y;
        depthTextureDescriptor.pixelFormat = MTLPixelFormatDepth24Unorm_Stencil8;
        depthTextureDescriptor.mipmapLevelCount = 1;
        depthTextureDescriptor.usage = MTLTextureUsageRenderTarget;
        
        m_DepthTexture = [context->m_Device newTextureWithDescriptor:colorTextureDescriptor];
        
        // Create render pass ----------
        m_RenderPassDescriptor = [[MTLRenderPassDescriptor alloc] init];
        m_RenderPassDescriptor.colorAttachments[0].texture = m_ColorTexture;
        m_RenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        m_RenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
        m_RenderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0, 0, 0, 1);
//        m_RenderPassDescriptor.depthAttachment.texture = m_DepthTexture;
//        m_RenderPassDescriptor.depthAttachment.loadAction = MTLLoadActionClear;
//        m_RenderPassDescriptor.depthAttachment.storeAction = MTLStoreActionStore;
//        m_RenderPassDescriptor.depthAttachment.clearDepth = 1.0;
        

    }

    void MetalFramebuffer::SetProperties(const FramebufferProperties &Properties)
    {
        m_Properties = Properties;
        Invalidate();
    }

    void MetalFramebuffer::Resize(uint32 width, uint32 height)
    {
        m_Properties.Size = {(float)width, (float)height};
        Invalidate();
    }

} // namespace Spark
