#pragma once

#include "Spark/Renderer/IBuffer.h"

namespace Spark
{
    
class OpenGLVertexBuffer : public IVertexBuffer
{
public:
    OpenGLVertexBuffer(float* vertices, uint32 size);
    virtual ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual BufferLayout GetLayout() const override;
    virtual void SetLayout(const BufferLayout& layout) override;

private:
    BufferLayout m_Layout = {};
    uint32 m_RendererID;
};

class OpenGLIndexBuffer : public IIndexBuffer
{
public:
    OpenGLIndexBuffer(uint32* indices, uint32 count);
    virtual ~OpenGLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual inline uint32 GetCount() const override { return m_Count; }
private:
    uint32 m_RendererID;
    uint32 m_Count;
};

} // namespace Spark