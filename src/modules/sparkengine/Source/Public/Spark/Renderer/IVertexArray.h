#pragma once

#include <memory>
#include "Spark/Renderer/IBuffer.h"

#include "sparkengine.api.gen.h"

namespace Spark
{

/**
 * Interface to define a VertexArray for plataform especific APIs.
 */
class SPARKENGINE_API IVertexArray
{
public:
    virtual ~IVertexArray() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer) = 0;

    virtual const std::vector<std::shared_ptr<IVertexBuffer>>& GetVertexBuffers() const = 0;
    virtual const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const = 0;

    static IVertexArray* Create();
};

}