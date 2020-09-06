#pragma once
#include "Spark/Core/CoreTypes.h"
#include "Spark/Core/PlatformWindow.h"
#include "Spark/Core/LayerStack.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/IBuffer.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/ImGui/ImGuiLayer.h"

#include "Spark/Renderer/OrthographicCamera.h"

#include <sparkengine.api.gen.h>

namespace Spark
{
    class SPARKENGINE_API Application
    {
    public:
        Application(const char* Name = "");
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline IPlatformWindow& GetWindow() {return *m_PlatformWindow; }

        inline static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        Ref<ImGuiLayer> m_ImGuiLayer;
        static Application* s_Instance;
        LayerStack m_LayerStack;
        std::unique_ptr<IPlatformWindow> m_PlatformWindow;
        bool m_Running = true;
        bool m_Minimized = false;

    };

    Application* CreateApplication();
    
}
