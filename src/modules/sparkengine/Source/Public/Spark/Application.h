#pragma once
#include "Spark/CoreTypes.h"
#include "Spark/PlatformWindow.h"
#include "Spark/LayerStack.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/IBuffer.h"
#include "Spark/Renderer/IVertexArray.h"
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

        std::shared_ptr<IShader> m_Shader;
        std::shared_ptr<IVertexBuffer> m_VertexBuffer;
        std::shared_ptr<IIndexBuffer> m_IndexBuffer;
        std::shared_ptr<IVertexArray> m_VertexArray;
    };

    Application* CreateApplication();
    
}

