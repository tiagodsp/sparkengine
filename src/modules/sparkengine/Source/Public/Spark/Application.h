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

        inline IPlatformWindow& GetWindow() {return *m_PlatformWindow; }

        inline static Application& Get() { return *s_Instance; }

    private:
        static Application* s_Instance;
        
        std::unique_ptr<IPlatformWindow> m_PlatformWindow;
        bool m_Running = true;

        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
    
}

