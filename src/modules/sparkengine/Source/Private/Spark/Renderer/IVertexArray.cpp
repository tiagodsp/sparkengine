#include "sparkengine.PCH.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/Renderer.h"

#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
#include "Spark/OpenGL/OpenGLVertexArray.h"
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL

#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
#include "Spark/Metal/MetalVertexArray.h"
#endif //SPARKENGINE_ENABLE_RENDERER_METAL

namespace Spark
{

Ref<IVertexArray> IVertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case PlatformRendererAPI::API::None:
        CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
        return nullptr;
#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
    case PlatformRendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexArray>();
        break;
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL
#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
    case PlatformRendererAPI::API::Metal:
        return std::make_shared<MetalVertexArray>();
        break;
#endif //SPARKENGINE_ENABLE_RENDERER_METAL
    }
}

}
