#include "sparkengine.PCH.h"
#include "Spark/Log.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Input.h"
#include "Spark/ImGui/ImGuiLayer.h"

#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/Renderer.h"


// TEMPORARY!!! --------------
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Platform/OpenGL/OpenGLShader.h"
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

        m_VertexArray.reset(IVertexArray::Create());

        // Verteice buffer...
        float vertices[3 * 7] =
        {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        m_VertexBuffer.reset(IVertexBuffer::Create(vertices, sizeof(vertices)));

        m_VertexBuffer->SetLayout(
        {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"}
        });

        // Index buffer...
        uint32 indices[3] = {0, 1, 2 };
        m_IndexBuffer.reset(IIndexBuffer::Create(indices, 3));
        
        // Create Vertex Array and set buffers...
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
            #version 330
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            out vec4 fragColor;

            void main()
            {
                gl_Position = vec4(a_Position, 1.0);
                fragColor = a_Color;
            }
        )";
        
        std::string fragmentSrc = R"(
            #version 330
            in vec4 fragColor;
            out vec4 color;

            void main()
            {
                color = fragColor;
            }
        )";
        

        m_Shader = std::make_unique<OpenGLShader>(vertexSrc, fragmentSrc);
        

    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while(m_Running)
        {
            RenderCommand::SetClearColor({0,0,0,0});
            RenderCommand::Clear();

            Renderer::BeginScene();
            m_Shader->Bind();
            Renderer::Submit(m_VertexArray);
            m_Shader->Unbind();
            Renderer::EndScene();

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