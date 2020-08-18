#include "sparkengine.PCH.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/OpenGL/OpenGLShader.h"

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
    
    Ref<IShader> IShader::Create(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource)
    {
        switch (Renderer::GetAPI())
        {
        case PlatformRendererAPI::API::None:
            CORE_ASSERT(false, "PlatformRendererAPI::API::None is currently not supported!");
        case PlatformRendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
        default:
            CORE_ASSERT(false, "PlatformRendererAPI::API not supported!");
        }
        return nullptr;
    }

    void ShaderLibrary::Add(const Ref<IShader>& shader)
    {

    }

    Ref<IShader> ShaderLibrary::Load(const std::string& filepath)
    {
        
    }
    Ref<IShader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        return nullptr;
    }
    Ref<IShader> ShaderLibrary::Get(const std::string& name)
    {
        return nullptr;
    }

} // namespace Spark
