#include "sparkengine.PCH.h"
#include "Spark/Log.h"
#include "Spark/Events/ApplicationEvent.h"

// TEMPORARY!!! --------------
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// ---------------------------

#include"Spark/Application.h"

namespace Spark
{
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
    {
        SC_ASSERT(!s_Instance, "Instance of Application alraedy exists!");
        s_Instance = this;
        m_PlatformWindow = std::unique_ptr<IPlatformWindow>(IPlatformWindow::Create());        
        m_PlatformWindow->SetEventCallback([&](Event& e){this->OnEvent(e);});
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while(m_Running)
        {
            glClearColor(0,0,0,0);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for(Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_PlatformWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent& e)
        {
            this->m_Running = false;
            return true;
        });
        
        //SC_LOG_INFO("{0}", e);

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.isHandled())
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