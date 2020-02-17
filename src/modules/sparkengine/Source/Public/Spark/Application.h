#pragma once
#include "Spark/CoreTypes.h"
#include "Spark/PlatformWindow.h"
#include "Spark/LayerStack.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/IBuffer.h"
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

        uint32 m_VertexArray; 
        std::unique_ptr<IShader> m_Shader;
        std::unique_ptr<IVertexBuffer> m_VertexBuffer;
        std::unique_ptr<IIndexBuffer> m_IndexBuffer;
    };

    Application* CreateApplication();
    
}

