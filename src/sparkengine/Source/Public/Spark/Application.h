#pragma once
#include "Spark/PlatformWindow.h"
#include <sparkengine.api.gen.h>

namespace Spark
{
    class SPARKENGINE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);
    private:
        std::unique_ptr<IPlatformWindow> m_PlatformWindow;
        bool m_Running = true;
    };

    Application* CreateApplication();
    
}

