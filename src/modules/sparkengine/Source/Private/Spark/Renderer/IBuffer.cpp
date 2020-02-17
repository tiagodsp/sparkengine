#include "sparkengine.PCH.h"
#include "Spark/Renderer/IBuffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Spark/Renderer/Renderer.h"

namespace Spark
{

IVertexBuffer* IVertexBuffer::Create(float* vertices, uint32 size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::None:
        SC_ASSERT(false, "RendererAPI::None is currently not supported.");
        return nullptr;
        break;
    case RendererAPI::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
        break;
    }
}

IIndexBuffer* IIndexBuffer::Create(uint32* indices, uint32 count)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::None:
        SC_ASSERT(false, "RendererAPI::None is currently not supported.");
        return nullptr;
        break;
    case RendererAPI::OpenGL:
        return new OpenGLIndexBuffer(indices, count);
        break;
    }
}

}