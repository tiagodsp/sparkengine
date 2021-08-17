#include "Spark/Metal/MetalFramebuffer.h"
#include <Metal/Metal.h>
#include "Spark/Renderer/Renderer.h"
#include "Spark/Metal/MetalPlatformRendererAPI.h"
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
        Ref<MetalPlatformRendererAPI> metalApi = std::static_pointer_cast<MetalPlatformRendererAPI>(Renderer::GetLowLevelAPI());
        m_CommandBuffer = [metalApi->m_CommandQueue commandBuffer];
        metalApi->m_CommandEncoder = [m_CommandBuffer renderCommandEncoderWithDescriptor:m_RenderPassDescriptor];
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
        
        id<MTLDevice> device = std::static_pointer_cast<MetalPlatformRendererAPI>(Renderer::GetLowLevelAPI())->m_Device;
        
        // Color attachment texture -------------
        MTLTextureDescriptor* colorTextureDescriptor = [[MTLTextureDescriptor alloc] init];
        colorTextureDescriptor.width = m_Properties.Size.x;
        colorTextureDescriptor.height = m_Properties.Size.y;
        colorTextureDescriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
        colorTextureDescriptor.mipmapLevelCount = 1;
        colorTextureDescriptor.usage = MTLTextureUsageRenderTarget;
        
        m_ColorTexture = [device newTextureWithDescriptor:colorTextureDescriptor];
        
        // Depth attachment texture --------------
        MTLTextureDescriptor* depthTextureDescriptor = [[MTLTextureDescriptor alloc] init];
        depthTextureDescriptor.width = m_Properties.Size.x;
        depthTextureDescriptor.height = m_Properties.Size.y;
        depthTextureDescriptor.pixelFormat = MTLPixelFormatDepth24Unorm_Stencil8;
        depthTextureDescriptor.mipmapLevelCount = 1;
        depthTextureDescriptor.usage = MTLTextureUsageRenderTarget;
        
        m_DepthTexture = [device newTextureWithDescriptor:colorTextureDescriptor];
        
        
        
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
