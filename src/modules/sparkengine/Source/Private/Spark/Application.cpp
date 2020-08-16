#include "sparkengine.PCH.h"
#include "Spark/Log.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Input.h"
#include "Spark/ImGui/ImGuiLayer.h"

#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/Renderer.h"

#include "Spark/Core/Platform.h"

// TEMPORARY!!! --------------
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Spark/OpenGL/OpenGLShader.h"
// ---------------------------

#include"Spark/Application.h"

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
            Timestep time = Platform::Get()->GetTime();
            Timestep delta = time - lastFrameTime;
            lastFrameTime = time;

            for (Layer *layer : m_LayerStack)
            {
                layer->OnUpdate(delta);
            }

            m_PlatformWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent &e) {
            this->m_Running = false;
            return true;
        });

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
}