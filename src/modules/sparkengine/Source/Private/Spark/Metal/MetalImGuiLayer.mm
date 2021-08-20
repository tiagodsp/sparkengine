#ifdef SPARKENGINE_ENABLE_RENDERER_METAL

#include "Spark/Metal/MetalImGuiLayer.h"

#include "Spark/Core/Application.h"
#include "Spark/Metal/MetalGraphicsContext.h"
#include "Spark/Renderer/Renderer.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_metal.h"
#include <memory>

#include "GLFW/glfw3.h"

namespace Spark
{
MetalImGuiLayer::MetalImGuiLayer(/* args */) : ImGuiLayer()
{
}

void MetalImGuiLayer::OnAttach()
{
	m_Context = ImGui::CreateContext();
	ImGui::StyleColorsDark();

	// ImGui configuration flags
	ImGuiIO &io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	// io.ConfigFlags  |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	GLFWwindow *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
	Ref<MetalGraphicsContext> metal_context =
	    std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplMetal_Init(metal_context->m_Device);
}

void MetalImGuiLayer::OnDetach()
{
	ImGui_ImplMetal_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void MetalImGuiLayer::Begin()
{
	Ref<MetalGraphicsContext> metal_context =
	    std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());
	ImGui_ImplMetal_NewFrame(metal_context->m_DefaultPass);
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void MetalImGuiLayer::End()
{
	ImGuiIO &io = ImGui::GetIO();
	Ref<MetalGraphicsContext> metal_context =
	    std::static_pointer_cast<MetalGraphicsContext>(Renderer::GetGraphicsContext());

	Application &app = Application::Get();
	IPlatformWindow &window = app.GetWindow();
	io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());

	// float time = (float)glfwGetTime();
	// io.DeltaTime = m_Time > 0.0f? (time - m_Time) : (1.0f / 60.0f);
	// m_Time = time;

	ImGui::Render();
	ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), metal_context->m_CommandBuffer,
	                               metal_context->m_CommandEncoder);

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow *window = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(window);
	}
}

void MetalImGuiLayer::OnImGuiRender(ImGuiContext *context)
{
	static bool show = true;
	ImGui::ShowDemoWindow(&show);
}

void MetalImGuiLayer::OnEvent(Event &event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MouseButtonPressedEvent>(
	    std::bind(&MetalImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(
	    std::bind(&MetalImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseScrollEvent>(std::bind(&MetalImGuiLayer::OnMouseScrollEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<MouseMovedEvent>(std::bind(&MetalImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<WindowResizeEvent>(
	    std::bind(&MetalImGuiLayer::OnWindowResizedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyPressedEvent>(std::bind(&MetalImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&MetalImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
	dispatcher.Dispatch<KeyTypedEvent>(std::bind(&MetalImGuiLayer::OnKeyTypedEvent, this, std::placeholders::_1));
}

// Events implementations -----------------------

bool MetalImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &e)
{
	ImGuiIO &io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = true;

	return false;
}

bool MetalImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e)
{
	ImGuiIO &io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = false;

	return false;
}

bool MetalImGuiLayer::OnMouseScrollEvent(MouseScrollEvent &e)
{
	ImGuiIO &io = ImGui::GetIO();
	io.MouseWheelH += e.GetXOffset();
	io.MouseWheel += e.GetYOffset();

	return false;
}

bool MetalImGuiLayer::OnMouseMovedEvent(MouseMovedEvent &e)
{
	ImGuiIO &io = ImGui::GetIO();
	io.MousePos = ImVec2(e.GetX(), e.GetY());

	return false;
}

bool MetalImGuiLayer::OnWindowResizedEvent(WindowResizeEvent &e)
{
	ImGuiIO &io = ImGui::GetIO();
	io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
	// glViewport(0, 0, e.GetWidth(), e.GetHeight());

	return false;
}

bool MetalImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &e)
{
	ImGuiIO &io = ImGui::GetIO();
	if (io.WantCaptureKeyboard)
	{
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return true;
	}

	return false;
}

bool MetalImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &e)
{
	ImGuiIO &io = ImGui::GetIO();
	if (io.WantCaptureKeyboard)
	{
		io.KeysDown[e.GetKeyCode()] = false;
		return true;
	}

	return false;
}

bool MetalImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &e)
{

	ImGuiIO &io = ImGui::GetIO();
	if (io.WantCaptureKeyboard)
	{
		int c = e.GetKeyCode();
		if (c > 0 && c < 0x10000)
			io.AddInputCharacter(static_cast<unsigned short>(c));
		return true;
	}
	return false;
}

}

#endif // SPARKENGINE_ENABLE_RENDERER_METAL