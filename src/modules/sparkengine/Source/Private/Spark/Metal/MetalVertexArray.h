#pragma once

#include "Spark/Core/CoreTypes.h"
#include <memory>
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/IBuffer.h"

namespace Spark
{

class MetalVertexArray : public IVertexArray
{
private:
    std::vector<Ref<IVertexBuffer>> m_VertexBuffers;
    Ref<IIndexBuffer> m_IndexBuffer;
    uint32 m_CurrentVertexBufferOffset;
public:
    MetalVertexArray(/* args */);
    virtual ~MetalVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) override;
    virtual void SetIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) override;

    virtual inline const std::vector<Ref<IVertexBuffer>>& GetVertexBuffers() const override {return m_VertexBuffers; }
    virtual inline const Ref<IIndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

};

} // namespace Spark
