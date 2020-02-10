#include "Spark/ImGui/ImGuiLayer.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "Spark/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Spark/Events/MouseEvent.h"
#include "Spark/Log.h"

namespace Spark
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
    }

    void ImGuiLayer::OnUpdate()
    {

        ImGuiIO& io = ImGui::GetIO();
        
        Application& app = Application::Get();
        IPlatformWindow& window = app.GetWindow();
        io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());
        
        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    void ImGuiLayer::OnEvent(Event& event)
    {
        if(event.GetEventType() == EventType::MouseButtonPressed)
        {
            MouseButtonPressedEvent& mbpe = static_cast<MouseButtonPressedEvent&>(event);
            SC_LOG_WARN(mbpe.ToString());
        }
    }
}