#pragma once
#include "Spark/PlatformWindow.h"
#include "Spark/LayerStack.h"
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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        std::unique_ptr<IPlatformWindow> m_PlatformWindow;
        bool m_Running = true;

        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
    
}

