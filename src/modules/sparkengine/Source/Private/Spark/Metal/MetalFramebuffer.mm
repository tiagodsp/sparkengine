#ifdef SPARKENGINE_ENABLE_RENDERER_METAL

#include "Spark/Metal/MetalFramebuffer.h"
#include "Spark/Metal/MetalGraphicsContext.h"
#include "Spark/Renderer/Renderer.h"
#include <Metal/Metal.h>
namespace Spark
{
	MetalFramebuffer::MetalFramebuffer(const FramebufferProperties &Properties) : m_Properties(Properties)
	{
		Invalidate();
	}

	MetalFramebuffer::~MetalFramebuffer()
	{
		[m_ColorTexture release];
		[m_DepthTexture release];
		[m_RenderPassDescriptor release];

		[m_CommandBuffer release];
		[m_CommandEncoder release];
	}

	void MetalFramebuffer::Bind()
	{
		Ref<MetalGraphicsContext> context =
			std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
		// set viewport size

		// Create command buffer, encoder and drawable surface for this framebuffer ----------
		// context->m_Surface = [context->m_Layer nextDrawable];
		// m_RenderPassDescriptor.colorAttachments[0].texture = context->m_Surface.texture;

		m_CommandBuffer = [context->m_CommandQueue commandBuffer];
		m_CommandEncoder = [m_CommandBuffer renderCommandEncoderWithDescriptor:m_RenderPassDescriptor];

		context->m_CommandBuffer = m_CommandBuffer;
		context->m_CommandEncoder = m_CommandEncoder;
	}

	void MetalFramebuffer::Unbind()
	{
		// Implement Unbind...
	}

	void MetalFramebuffer::Invalidate()
	{
		if (m_RenderPassDescriptor)
		{
			[m_ColorTexture release];
			// [m_DepthTexture release];
			[m_RenderPassDescriptor release];
		}

		// Get metal context
		Ref<MetalGraphicsContext> context =
			std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());

		// Create color attachment texture
		MTLTextureDescriptor *ColorTextureDescriptor =
			[MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatBGRA8Unorm
															   width:m_Properties.Size.x
															  height:m_Properties.Size.y
														   mipmapped:NO];
		ColorTextureDescriptor.usage = MTLTextureUsageShaderRead;
		m_ColorTexture = [context->m_Device newTextureWithDescriptor:ColorTextureDescriptor];
		[ColorTextureDescriptor release];

		// Get pointer address from m_ColorTexture as unint64 address
		auto ptr = (__bridge void *)m_ColorTexture;
		m_ColorAttachmentRendererID = (uintptr_t)ptr;

		// Create render pass ----------
		m_RenderPassDescriptor = [[MTLRenderPassDescriptor alloc] init];
		m_RenderPassDescriptor.colorAttachments[0].texture = m_ColorTexture;
		m_RenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
		m_RenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
		m_RenderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0, 0, 0, 1);
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

#endif // SPARKENGINE_ENABLE_RENDERER_METAL