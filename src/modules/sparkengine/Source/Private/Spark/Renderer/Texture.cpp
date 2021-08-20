#include "sparkengine.PCH.h"
#include "Spark/Renderer/Texture.h"
#include "Spark/Renderer/Renderer.h"

#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
#include "Spark/OpenGL/OpenGLTexture2D.h"
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL

#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
#include "Spark/Metal/MetalTexture2D.h"
#endif //SPARKENGINE_ENABLE_RENDERER_METAL

namespace Spark
{
    Ref<Texture2D> Texture2D::Create(uint32 Width, uint32 Height, TextureFormat TextureFormat)
    {
        switch (Renderer::GetAPI())
        {
        case PlatformRendererAPI::API::None:
            return nullptr;
            break;
#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
        case PlatformRendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(Width, Height, TextureFormat);
            break;
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL
#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
        case PlatformRendererAPI::API::Metal:
            return std::make_shared<MetalTexture2D>(Width, Height, TextureFormat);
            break;
#endif //SPARKENGINE_ENABLE_RENDERER_METAL
        default:
            return nullptr;
        }
    }

    Ref<Texture2D> Texture2D::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
        case PlatformRendererAPI::API::None:
            return nullptr;
            break;
#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
        case PlatformRendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(filepath);
            break;
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL
#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
        case PlatformRendererAPI::API::Metal:
            return std::make_shared<MetalTexture2D>(filepath);
            break;
#endif //SPARKENGINE_ENABLE_RENDERER_METAL
        default:
            return nullptr;
        }
    }
}
