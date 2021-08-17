#pragma once

#include "Spark/Renderer/IBuffer.h"
#include <Metal/Metal.h>

namespace Spark
{
    
class MetalVertexBuffer : public IVertexBuffer
{
    friend class MetalPlatformRendererAPI;
public:
    MetalVertexBuffer(float* vertices, uint32 size);
    virtual ~MetalVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;
    
    virtual void SetOffset(uint32 offset) override { m_Offset = offset; }
    virtual uint32 GetOffset() override { return m_Offset; }
    virtual uint32 GetSize() override {return m_Size; };
                           

    virtual BufferLayout GetLayout() const override;
    virtual void SetLayout(const BufferLayout& layout) override;

private:
    BufferLayout m_Layout = {};
    id<MTLBuffer> m_Buffer;
    uint32 m_Offset;
    uint32 m_Size;
};

class MetalIndexBuffer : public IIndexBuffer
{
    friend class MetalPlatformRendererAPI;
public:
    MetalIndexBuffer(uint32* indices, uint32 count);
    virtual ~MetalIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual inline uint32 GetCount() const override { return m_Count; }
private:
    id<MTLBuffer> m_Buffer;
    uint32 m_Count;
};

} // namespace Spark
