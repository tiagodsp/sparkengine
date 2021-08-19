#include "sparkengine.PCH.h"
#include "MetalPlatformRendererAPI.h"
#include "MetalGraphicsContext.h"
#include "Spark/Metal/MetalBuffer.h"
#include <Metal/Metal.h>

namespace Spark
{

    MetalPlatformRendererAPI::MetalPlatformRendererAPI(/* args */)
    {
    }

    MetalPlatformRendererAPI::~MetalPlatformRendererAPI()
    {
    }

    void MetalPlatformRendererAPI::Init()
    {
        s_API = API::Metal; //Set default render as Metal;
    }

    void MetalPlatformRendererAPI::SetClearColor(const glm::vec4 color)
    {
        m_ClearColor = color;
        m_GraphicsContext->m_DefaultPass.colorAttachments[0].clearColor = MTLClearColorMake(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    }

    void MetalPlatformRendererAPI::Clear()
    {
        Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(GetGraphicsContext());
        
        m_GraphicsContext->m_Surface = [m_GraphicsContext->m_Layer nextDrawable];
        m_GraphicsContext->m_DefaultPass.colorAttachments[0].texture = m_GraphicsContext->m_Surface.texture;

        context->m_CommandBuffer = [context->m_CommandQueue commandBuffer];
        context->m_CommandEncoder = [context->m_CommandBuffer renderCommandEncoderWithDescriptor:m_GraphicsContext->m_DefaultPass];
    }

    void MetalPlatformRendererAPI::DrawIndexed(const Ref<IVertexArray> &vertexArray)
    {
        Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(GetGraphicsContext());
        Ref<MetalIndexBuffer> ib = std::static_pointer_cast<MetalIndexBuffer>(vertexArray->GetIndexBuffer());
        
        [context->m_CommandEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:ib->GetCount() indexType:MTLIndexTypeUInt32 indexBuffer:ib->m_Buffer indexBufferOffset:0];
    }

    void MetalPlatformRendererAPI::SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height)
    {
//        glViewport(X, Y, Width, Height);
    }

    void MetalPlatformRendererAPI::Commit()
    {
        Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(GetGraphicsContext());

        [context->m_CommandEncoder endEncoding];
        [context->m_CommandBuffer presentDrawable:context->m_Surface];
        [context->m_CommandBuffer commit];
        [context->m_CommandBuffer waitUntilCompleted];
        
        //        [context->m_Surface release];
        [context->m_CommandBuffer release];
        [context->m_CommandEncoder release];
    }

} // namespace Spark
