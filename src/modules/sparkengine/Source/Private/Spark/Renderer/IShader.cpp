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
        auto& name = shader->GetName();
        CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader {0} already exists!", name);
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<IShader>& shader)
    {
        CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader {0} already exists!", name);
        m_Shaders[name] = shader;
    }

    Ref<IShader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = IShader::Create(filepath);
        Add(shader);
        return shader;
    }
    Ref<IShader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = IShader::Create(filepath);
        Add(name, shader);
        return shader;
    }
    Ref<IShader> ShaderLibrary::Get(const std::string& name)
    {
        CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!", name);
        if(m_Shaders.find(name) != m_Shaders.end())
            return m_Shaders[name];
        return nullptr;
    }

} // namespace Spark
