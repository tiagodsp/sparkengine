#include "sparkengine.PCH.h"

#include "Spark/Log.h"

#include"Spark/Application.h"

namespace Spark
{
    Application::Application()
    {
        m_PlatformWindow = std::unique_ptr<IPlatformWindow>(IPlatformWindow::Create());
        m_PlatformWindow->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while(m_Running)
        {
            m_PlatformWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        SC_LOG_INFO("{0}", e);
    }

}