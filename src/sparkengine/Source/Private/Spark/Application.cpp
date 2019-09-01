#include "sparkengine.PCH.h"

#include "Spark/Log.h"
#include "Spark/Events/ApplicationEvent.h"

#include"Spark/Application.h"

namespace Spark
{
    Application::Application()
    {
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
            m_PlatformWindow->OnUpdate();

            for(Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }
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
        
        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.isHandled())
                break;
        }

        SC_LOG_INFO("{0}", e);
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }
    
    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }
}