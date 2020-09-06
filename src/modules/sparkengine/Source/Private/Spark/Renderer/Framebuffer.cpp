#include "sparkengine.PCH.h"
#include "Spark/Renderer/Framebuffer.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/OpenGL/OpenGLFramebuffer.h"

namespace Spark
{
    Ref<IFramebuffer> IFramebuffer::Create(const FramebufferProperties& Properties)
    {
        switch (Renderer::GetAPI())
        {
        case PlatformRendererAPI::API::OpenGL:
            return std::make_shared<OpenGLFramebuffer>(Properties);
        case PlatformRendererAPI::API::None:
        default:
            CORE_ASSERT(false, "RendererAPI is currently not supported.");
            return nullptr;
        }
    }
    
} // namespace Spark
