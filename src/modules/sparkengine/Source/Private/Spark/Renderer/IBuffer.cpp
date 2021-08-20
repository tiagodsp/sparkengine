#include "sparkengine.PCH.h"
#include "Spark/Renderer/IBuffer.h"

#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
#include "Spark/OpenGL/OpenGLBuffer.h"
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL

#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
#include "Spark/Metal/MetalBuffer.h"
#endif //SPARKENGINE_ENABLE_RENDERER_METAL

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
#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
    case PlatformRendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        break;
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL
#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
    case PlatformRendererAPI::API::Metal:
        return std::make_shared<MetalVertexBuffer>(vertices, size);
        break;
#endif //SPARKENGINE_ENABLE_RENDERER_METAL
    default:
        CORE_ASSERT(false, "RendererAPI is currently not supported.");
        return nullptr;
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
#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
    case PlatformRendererAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(indices, count);
        break;
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL
#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
    case PlatformRendererAPI::API::Metal:
        return std::make_shared<MetalIndexBuffer>(indices, count);
        break;
#endif //SPARKENGINE_ENABLE_RENDERER_METAL
    default:
        CORE_ASSERT(false, "RendererAPI is currently not supported.");
        return nullptr;
    }
}

}
