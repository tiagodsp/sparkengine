#include "sparkengine.PCH.h"
#include "Spark/Renderer/Framebuffer.h"
#include "Spark/Renderer/Renderer.h"

#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
#include "Spark/OpenGL/OpenGLFramebuffer.h"
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL

#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
#include "Spark/Metal/MetalFramebuffer.h"
#endif //SPARKENGINE_ENABLE_RENDERER_METAL

namespace Spark
{
    Ref<IFramebuffer> IFramebuffer::Create(const FramebufferProperties& Properties)
    {
        switch (Renderer::GetAPI())
        {
#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
        case PlatformRendererAPI::API::OpenGL:
            return std::make_shared<OpenGLFramebuffer>(Properties);
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL
#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
        case PlatformRendererAPI::API::Metal:
            return std::make_shared<MetalFramebuffer>(Properties);
#endif //SPARKENGINE_ENABLE_RENDERER_METAL
        case PlatformRendererAPI::API::None:
        default:
            CORE_ASSERT(false, "RendererAPI is currently not supported.");
            return nullptr;
        }
    }
    
} // namespace Spark
