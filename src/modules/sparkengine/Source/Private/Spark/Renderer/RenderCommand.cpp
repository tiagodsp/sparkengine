#include "sparkengine.PCH.h"
#include "Spark/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLPlatformRendererAPI.h"

namespace Spark
{

PlatformRendererAPI* RenderCommand::s_RendererAPI = new OpenGLPlatformRendererAPI();

}