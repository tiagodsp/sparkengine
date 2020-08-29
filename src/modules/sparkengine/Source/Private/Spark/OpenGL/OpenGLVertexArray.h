#pragma once

#include "Spark/Core/CoreTypes.h"
#include <memory>
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/IBuffer.h"

namespace Spark
{

class OpenGLVertexArray : public IVertexArray
{
private:
    uint32 m_RendererID;
    std::vector<Ref<IVertexBuffer>> m_VertexBuffers;
    Ref<IIndexBuffer> m_IndexBuffer;
public:
    OpenGLVertexArray(/* args */);
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) override;
    virtual void SetIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) override;

    virtual inline const std::vector<Ref<IVertexBuffer>>& GetVertexBuffers() const override {return m_VertexBuffers; }
    virtual inline const Ref<IIndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

};

} // namespace Spark