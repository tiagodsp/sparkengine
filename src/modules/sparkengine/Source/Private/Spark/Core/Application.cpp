#include "sparkengine.PCH.h"
#include "Spark/Core/Log.h"
#include "Spark/Core/Input.h"
#include "Spark/ImGui/ImGuiLayer.h"

#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/Renderer.h"

#include "Spark/Core/Platform.h"

// TEMPORARY!!! --------------
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Spark/OpenGL/OpenGLShader.h"
// ---------------------------

#include"Spark/Core/Application.h"

namespace Spark
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        CORE_ASSERT(!s_Instance, "Instance of Application alraedy exists!");
        s_Instance = this;
        m_PlatformWindow = std::unique_ptr<IPlatformWindow>(IPlatformWindow::Create());
        m_PlatformWindow->SetEventCallback([&](Event &e) { this->OnEvent(e); });

        Renderer::Init();

        this->PushOverlay(new Spark::ImGuiLayer());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        Timestep lastFrameTime;
        while (m_Running)
        {
            // Calculate delta time.
            Timestep time = Platform::Get()->GetTime();
            Timestep delta = time - lastFrameTime;
            lastFrameTime = time;

            // If application is minimized, pause everything...
            if (!m_Minimized)
            {
                // Update all layers.
                for (Layer *layer : m_LayerStack)
                {
                    layer->OnUpdate(delta);
                }
            }
            // Update Window.
            m_PlatformWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e)
    {
        // Dispatch window related events.
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

        // Dispatch events to each layer.
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.isHandled())
                break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }
    
    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
    
    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if(e.GetWidth() == 0 && e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }
}