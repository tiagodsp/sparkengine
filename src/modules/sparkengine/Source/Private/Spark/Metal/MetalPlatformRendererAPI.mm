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
        m_GraphicsContext = std::static_pointer_cast<MetalGraphicsContext>(GetGraphicsContext());
        m_Device = m_GraphicsContext->m_Device;
        m_CommandQueue = [m_Device newCommandQueue];
        

        m_DefaultPass = [MTLRenderPassDescriptor renderPassDescriptor];
        m_DefaultPass.colorAttachments[0].clearColor = MTLClearColorMake(0, 0, 0, 1);
        m_DefaultPass.colorAttachments[0].loadAction = MTLLoadActionClear;
        m_DefaultPass.colorAttachments[0].storeAction = MTLStoreActionStore;
//        m_DefaultPass.colorAttachments[0].texture = m_GraphicsContext->m_Surface.texture;
        
    }

    void MetalPlatformRendererAPI::SetClearColor(const glm::vec4 color)
    {
        m_ClearColor = color;
        m_DefaultPass.colorAttachments[0].clearColor = MTLClearColorMake(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    }

    void MetalPlatformRendererAPI::Clear()
    {
        Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(GetGraphicsContext());
        
        m_GraphicsContext->m_Surface = [m_GraphicsContext->m_Layer nextDrawable];
        m_DefaultPass.colorAttachments[0].texture = m_GraphicsContext->m_Surface.texture;

        m_CommandBuffer = [m_CommandQueue commandBuffer];
        m_CommandEncoder = [m_CommandBuffer renderCommandEncoderWithDescriptor:m_DefaultPass];
    }

    void MetalPlatformRendererAPI::DrawIndexed(const Ref<IVertexArray> &vertexArray)
    {
        Ref<MetalIndexBuffer> ib = std::static_pointer_cast<MetalIndexBuffer>(vertexArray->GetIndexBuffer());
        
        [m_CommandEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:ib->GetCount() indexType:MTLIndexTypeUInt32 indexBuffer:ib->m_Buffer indexBufferOffset:0];
    }

    void MetalPlatformRendererAPI::SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height)
    {
//        glViewport(X, Y, Width, Height);
    }

    void MetalPlatformRendererAPI::Commit()
    {
        MetalGraphicsContext* context = static_cast<MetalGraphicsContext*>(GetGraphicsContext().get());

        [m_CommandEncoder endEncoding];
        [m_CommandBuffer presentDrawable:context->m_Surface];
        [m_CommandBuffer commit];
        [m_CommandBuffer waitUntilCompleted];
        
        //        [context->m_Surface release];
        [m_CommandBuffer release];
        [m_CommandEncoder release];
    }

} // namespace Spark
