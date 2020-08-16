#include "sparkengine.PCH.h"
#include "Spark/Renderer/IBuffer.h"
#include "Spark/OpenGL/OpenGLBuffer.h"
#include "Spark/Renderer/Renderer.h"

namespace Spark
{

Ref<IVertexBuffer> IVertexBuffer::Create(float* vertices, uint32 size)
{
    switch (Renderer::GetAPI())
    {
    case PlatformRendererAPI::API::None:
        CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
        return nullptr;
        break;
    case PlatformRendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        break;
    }
}

Ref<IIndexBuffer> IIndexBuffer::Create(uint32* indices, uint32 count)
{
    switch (Renderer::GetAPI())
    {
    case PlatformRendererAPI::API::None:
        CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
        return nullptr;
        break;
    case PlatformRendererAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(indices, count);
        break;
    }
}

}