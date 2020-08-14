#include "sparkengine.PCH.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Spark
{

    Ref<IShader> IShader::Create(const std::string &filepath)
    {
        switch (Renderer::GetAPI())
        {
        case PlatformRendererAPI::API::None:
            CORE_ASSERT(false, "PlatformRendererAPI::API::None is currently not supported!");
        case PlatformRendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(filepath);
        default:
            CORE_ASSERT(false, "PlatformRendererAPI::API not supported!");
        }
        return nullptr;
    }
    
    Ref<IShader> IShader::Create(const std::string &vertexSource, const std::string &fragmentSource)
    {
        switch (Renderer::GetAPI())
        {
        case PlatformRendererAPI::API::None:
            CORE_ASSERT(false, "PlatformRendererAPI::API::None is currently not supported!");
        case PlatformRendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(vertexSource, fragmentSource);
        default:
            CORE_ASSERT(false, "PlatformRendererAPI::API not supported!");
        }
        return nullptr;
    }

} // namespace Spark
