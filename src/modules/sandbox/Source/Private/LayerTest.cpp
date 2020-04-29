#include "LayerTest.h"

#include "Spark/Events/KeyEvent.h"
#include "Spark/KeyCodes.h"
#include "Spark/Input.h"

#include "glm/gtc/matrix_transform.hpp"

DECLARE_LOG_CATEGORY(LayerTest);

namespace Sandbox
{

LayerTest::LayerTest()
{
    m_VertexArray.reset(Spark::IVertexArray::Create());

    // Verteice buffer...
    float vertices[4 * 5] =
    {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    m_VertexBuffer.reset(Spark::IVertexBuffer::Create(vertices, sizeof(vertices)));

    m_VertexBuffer->SetLayout(
    {
        {Spark::ShaderDataType::Float3, "a_Position"},
        {Spark::ShaderDataType::Float2, "a_TexCord"}
    });

    // Index buffer...
    uint32 indices[6] = {0, 1, 2, 0, 2, 3};
    m_IndexBuffer.reset(Spark::IIndexBuffer::Create(indices, 6));

    // Create Vertex Array and set buffers...
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    std::string vertexSrc = R"(
            #version 330
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCord;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec4 fragColor;

            void main()
            {
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
                fragColor = vec4(a_TexCord, 0, 1);
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

    m_Shader = Spark::IShader::Create(vertexSrc, fragmentSrc);
}

LayerTest::~LayerTest()
{
}

// Spark::Layer interface implementation ---------

void LayerTest::OnAttach()
{
}

void LayerTest::OnDetach()
{
}

void LayerTest::OnUpdate(Spark::Timestep delta)
{
    //LOGI(LayerTest, "Delta time: {0}s | {1}ms", delta.GetTimeSeconds(), delta.GetTimeMilis());

    if (Spark::Input::IsKeyPressed(SPARK_KEY_RIGHT))
        m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(m_CameraSpeed * delta, 0, 0));
    else if (Spark::Input::IsKeyPressed(SPARK_KEY_LEFT))
        m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(-m_CameraSpeed * delta, 0, 0));

    if (Spark::Input::IsKeyPressed(SPARK_KEY_UP))
        m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0, m_CameraSpeed * delta, 0));
    else if (Spark::Input::IsKeyPressed(SPARK_KEY_DOWN))
        m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3(0, -m_CameraSpeed * delta, 0));

    Spark::RenderCommand::SetClearColor({0, 0, 0, 0});
    Spark::RenderCommand::Clear();

    Spark::Renderer::BeginScene(m_Camera);
    Spark::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));
    Spark::Renderer::EndScene();
}

void LayerTest::OnEvent(Spark::Event &event)
{
    Spark::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Spark::KeyPressedEvent>(std::bind(&LayerTest::HandleKeyInputEvents, this, std::placeholders::_1));
}
// ------------------------------------------------

bool LayerTest::HandleKeyInputEvents(Spark::Event &event)
{
    return false;
}

} // namespace Sandbox