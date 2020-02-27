#include "sparkengine.PCH.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Spark
{
    
std::shared_ptr<IShader> IShader::Create(const std::string &vertexSource, const std::string &fragmentSource)
{
    switch (Renderer::GetAPI())
    {
    case PlatformRendererAPI::API::None:
        return nullptr;
        break;
    case PlatformRendererAPI::API::OpenGL:
        return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
        break;
    default:
        return nullptr;
    }
}

} // namespace Spark
