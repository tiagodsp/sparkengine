#include "sparkengine.PCH.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/Renderer.h"

#include "Spark/OpenGL/OpenGLVertexArray.h"
#include "Spark/Metal/MetalVertexArray.h"

namespace Spark
{

Ref<IVertexArray> IVertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case PlatformRendererAPI::API::None:
        CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
        return nullptr;
    case PlatformRendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexArray>();
        break;
    case PlatformRendererAPI::API::Metal:
        return std::make_shared<MetalVertexArray>();
        break;
    }
}

}
