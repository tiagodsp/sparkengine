#include "sparkengine.PCH.h"
#include "MetalBuffer.h"

#include "Spark/Metal/MetalGraphicsContext.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/Metal/MetalPlatformRendererAPI.h"

namespace Spark
{

// MetalVertexBuffer methods definitions ----------------
MetalVertexBuffer::MetalVertexBuffer(float* vertices, uint32 size)
{
    Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
    m_Buffer = [context->m_Device newBufferWithBytes:vertices length:size options:MTLResourceOptionCPUCacheModeDefault];
    m_Offset = 0;
    m_Size = size;
}

MetalVertexBuffer::~MetalVertexBuffer()
{
    [m_Buffer release];
}

void MetalVertexBuffer::Bind() const
{
    Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
    [context->m_CommandEncoder setVertexBuffer:m_Buffer offset:m_Offset atIndex:0];
}

void MetalVertexBuffer::Unbind() const
{
    // TODO - Implement MetalVertexBuffer::Unbind();
}

BufferLayout MetalVertexBuffer::GetLayout() const
{
    return m_Layout;
}

void MetalVertexBuffer::SetLayout(const BufferLayout& layout)
{
    m_Layout = layout;
}

// -------------------------------------------------------

// MetalIndexBuffer methods definitions ----------------
MetalIndexBuffer::MetalIndexBuffer(uint32* indices, uint32 count)
{
    m_Count = count;
    
    Ref<MetalGraphicsContext> context = std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
    m_Buffer = [context->m_Device newBufferWithBytes:indices length:count * sizeof(uint32) options:MTLResourceOptionCPUCacheModeDefault];
}

MetalIndexBuffer::~MetalIndexBuffer()
{
    [m_Buffer release];
}

void MetalIndexBuffer::Bind() const
{
    // Metal index buffer does not bind;
}

void MetalIndexBuffer::Unbind() const
{
    // Metal index buffer does not bind;
}

} // namespace Spark
