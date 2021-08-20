#include "Spark/ImGui/ImGuiLayer.h"
#include "Spark/Core/CoreTypes.h"
#include "Spark/Metal/MetalImGuiLayer.h"
#include "Spark/OpenGL/OpenGLImGuiLayer.h"
#include "Spark/Renderer/PlatformRendererAPI.h"
#include <cstddef>
#include <memory>

namespace Spark
{

Ref<ImGuiLayer> ImGuiLayer::Create()
{
	switch (PlatformRendererAPI::GetAPI())
	{
	case PlatformRendererAPI::API::None:
		ASSERT(false, "Renderer API not supported.");
        return nullptr;
		break;
	case PlatformRendererAPI::API::OpenGL:
		return std::make_shared<OpenGLImGuiLayer>();
		break;
	case PlatformRendererAPI::API::Metal:
		return std::make_shared<MetalImGuiLayer>();
		break;
	default:
		ASSERT(false, "Renderer API not supported.");
        return nullptr;
	}
}

} // namespace Spark