#include "sparkengine.PCH.h"
#include "Spark/Log.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Input.h"
#include "Spark/ImGui/ImGuiLayer.h"

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

        this->PushOverlay(new Spark::ImGuiLayer());

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertices[3 * 3] =
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

        uint32 indices[3] = {0, 1, 2 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
            
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