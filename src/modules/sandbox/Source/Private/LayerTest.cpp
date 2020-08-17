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
    m_VertexArray = Spark::IVertexArray::Create();

    // Verteice buffer...
    float vertices[4 * 5] =
    {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    m_VertexBuffer = Spark::IVertexBuffer::Create(vertices, sizeof(vertices));

    m_VertexBuffer->SetLayout(
    {
        {Spark::ShaderDataType::Float3, "a_Position"},
        {Spark::ShaderDataType::Float2, "a_TexCoord"}
    });

    // Index buffer...
    uint32 indices[6] = {0, 1, 2, 0, 2, 3};
    m_IndexBuffer = Spark::IIndexBuffer::Create(indices, 6);

    // Create Vertex Array and set buffers...
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    m_Shader = Spark::IShader::Create("Assets\\Shaders\\Texture.glsl");
    //m_Shader = Spark::IShader::Create(vertexSrc, fragmentSrc);

    m_Texture = Spark::Texture2D::Create("./Assets/Textures/UV_Grid_Sm.jpg");
    m_AlphaTexture = Spark::Texture2D::Create("./Assets/Textures/digital.png");
    m_Shader->Bind();
    m_Shader->UploadUniformInt("u_Texture", 0);

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

    //Start scene rendering
    Spark::Renderer::BeginScene(m_Camera);
    
    m_Texture->Bind();
    Spark::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));
    m_AlphaTexture->Bind();
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