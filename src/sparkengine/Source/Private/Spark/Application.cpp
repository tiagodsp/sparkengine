#include "sparkengine.PCH.h"

#include"Spark/Application.h"

namespace Spark
{
    Application::Application()
    {
        m_PlatformWindow = std::unique_ptr<IPlatformWindow>(IPlatformWindow::Create());
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

}