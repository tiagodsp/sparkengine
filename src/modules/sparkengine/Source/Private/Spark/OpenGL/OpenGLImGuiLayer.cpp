#include "Spark/OpenGL/OpenGLImGuiLayer.h"
#include "Spark/Core/Application.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "Spark/Core/Log.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Spark
{
    OpenGLImGuiLayer::OpenGLImGuiLayer()
    {
    }

    void OpenGLImGuiLayer::OnAttach()
    {
        m_Context = ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        // io.ConfigFlags  |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags  |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags  |= ImGuiConfigFlags_DockingEnable;

        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        ImGui_ImplGlfw_InitForOpenGL(window, false);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void OpenGLImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void OpenGLImGuiLayer::OnImGuiRender(ImGuiContext* context)
    {
        // static bool show = true;
        // ImGui::ShowDemoWindow(&show);
    }

    void OpenGLImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    
    void OpenGLImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        
        Application& app = Application::Get();
        IPlatformWindow& window = app.GetWindow();
        io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());     

        // float time = (float)glfwGetTime();
        // io.DeltaTime = m_Time > 0.0f? (time - m_Time) : (1.0f / 60.0f);
        // m_Time = time;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* window =glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(window);
        }
    }
    
    void OpenGLImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&OpenGLImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&OpenGLImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseScrollEvent>(std::bind(&OpenGLImGuiLayer::OnMouseScrollEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseMovedEvent>(std::bind(&OpenGLImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&OpenGLImGuiLayer::OnWindowResizedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&OpenGLImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&OpenGLImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyTypedEvent>(std::bind(&OpenGLImGuiLayer::OnKeyTypedEvent, this, std::placeholders::_1));

    }

    // Events implementations -----------------------

    bool OpenGLImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;
        
        return false;
    }

    bool OpenGLImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;
        
        return false;
    }

    bool OpenGLImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();
        
        return false;
    }

    bool OpenGLImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());
        
        return false;
    }

    bool OpenGLImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
        
        return false;
    }
    
    bool OpenGLImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        if(io.WantCaptureKeyboard)
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
    
    bool OpenGLImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        if(io.WantCaptureKeyboard)
        {
            io.KeysDown[e.GetKeyCode()] = false;
            return true;
        }
        
        return false;
    }

    bool OpenGLImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {

        ImGuiIO& io = ImGui::GetIO();
        if(io.WantCaptureKeyboard)
        {
            int c = e.GetKeyCode();
            if (c > 0 && c < 0x10000)
                io.AddInputCharacter(static_cast<unsigned short>(c));
            return true;
        }
        return false;
    }

}
