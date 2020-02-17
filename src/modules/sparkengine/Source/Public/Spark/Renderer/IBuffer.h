#pragma once

#include "Spark/CoreTypes.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

class SPARKENGINE_API IVertexBuffer
{
public:
    virtual ~IVertexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static IVertexBuffer* Create(float* vertices, uint32 size);
};

class SPARKENGINE_API IIndexBuffer
{
public:
    virtual ~IIndexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32 GetCount() const = 0;

    static IIndexBuffer* Create(uint32* indices, uint32 count);
};

} // namespace Spark
