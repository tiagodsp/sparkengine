#include "sparkengine.PCH.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Spark
{

IVertexArray* IVertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case PlatformRendererAPI::API::None:
        CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
        return nullptr;
        break;
    case PlatformRendererAPI::API::OpenGL:
        return new OpenGLVertexArray();
        break;
    }
}

}