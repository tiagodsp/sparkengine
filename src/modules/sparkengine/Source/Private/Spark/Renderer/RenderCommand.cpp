#include "sparkengine.PCH.h"
#include "Spark/Renderer/RenderCommand.h"

#include "Spark/OpenGL/OpenGLPlatformRendererAPI.h"
#include "Spark/Metal/MetalPlatformRendererAPI.h"

namespace Spark
{

Ref<PlatformRendererAPI> RenderCommand::s_RendererAPI = std::make_shared<MetalPlatformRendererAPI>();

}
