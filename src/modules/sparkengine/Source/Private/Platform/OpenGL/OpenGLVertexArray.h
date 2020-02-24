#pragma once

#include "Spark/CoreTypes.h"
#include <memory>
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/IBuffer.h"

namespace Spark
{

class OpenGLVertexArray : public IVertexArray
{
private:
    uint32 m_RendererID;
    std::vector<std::shared_ptr<IVertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IIndexBuffer> m_IndexBuffer;
public:
    OpenGLVertexArray(/* args */);
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) override;
    virtual void SetIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer) override;

    virtual inline const std::vector<std::shared_ptr<IVertexBuffer>>& GetVertexBuffers() const override {return m_VertexBuffers; }
    virtual inline const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

};

} // namespace Spark