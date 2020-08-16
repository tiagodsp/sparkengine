#include "sparkengine.PCH.h"
#include "Spark/Renderer/Texture.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/OpenGL/OpenGLTexture2D.h"

namespace Spark
{
    Ref<Texture2D> Texture2D::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
        case PlatformRendererAPI::API::None:
            return nullptr;
            break;
        case PlatformRendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(filepath);
            break;
        default:
            return nullptr;
        }
    }
}
