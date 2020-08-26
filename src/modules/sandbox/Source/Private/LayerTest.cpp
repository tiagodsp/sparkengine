#include "LayerTest.h"

#include "Spark/Events/KeyEvent.h"
#include "Spark/KeyCodes.h"
#include "Spark/Input.h"
#include "Spark/Core/GenericPlatform/GenericPlatformFile.h"
#include "Spark/Core/Misc/Paths.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Spark/Engine/World.h"
#include "Spark/Engine/Camera/CameraComponent.h"
#include "Spark/Engine/Mesh/MeshComponent.h"

DECLARE_LOG_CATEGORY(LayerTest);

namespace Sandbox
{

LayerTest::LayerTest()
{
    auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");
    //m_Shader = Spark::IShader::Create(vertexSrc, fragmentSrc);

    m_Texture = Spark::Texture2D::Create("./Assets/Textures/UV_Grid_Sm.jpg");
    m_AlphaTexture = Spark::Texture2D::Create("./Assets/Textures/digital.png");
    textureShader->Bind();
    textureShader->UploadUniformInt("u_Texture", 0);
    
    m_Camera = std::make_shared<Spark::OrthographicCamera>(-1.6f, 1.6f, -0.9f, 0.9f);
    m_World.reset<Spark::World>(new Spark::World());
    Spark::Entity& camera = m_World->GetCurrentLevel()->CreateEntity();
    camera.AddComponent<Spark::CameraComponent>(m_Camera);

    Spark::Entity& mesh = m_World->GetCurrentLevel()->CreateEntity();
    mesh.AddComponent<Spark::MeshComponent>("./Assets/Meshes/monkey.glb");


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
    
    m_World->Update(delta);

    Spark::RenderCommand::SetClearColor({0, 0, 0, 0});
    Spark::RenderCommand::Clear();

    //Start scene rendering
    Spark::Renderer::BeginScene(*m_Camera);

    auto& meshes = m_World->GetContext().view<Spark::MeshComponent, Spark::TransformComponent>();
    for(auto& m : meshes)
    {
        m_Texture->Bind();
        Spark::MeshComponent mc = m_World->GetContext().get<Spark::MeshComponent>(m);
        glm::mat4 transform = m_World->GetContext().get<Spark::TransformComponent>(m).Transform;
        
        for(auto& va : mc.GetVertexArrays())
        {
            Spark::Renderer::Submit(m_ShaderLibrary.Get("Texture"), va, transform);
        }
    }
    
    // m_Texture->Bind();
    // Spark::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_VertexArray, glm::mat4(1.0f));
    // m_AlphaTexture->Bind();
    // Spark::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_VertexArray, glm::mat4(1.0f));
    
    Spark::Renderer::EndScene();
}

void LayerTest::OnEvent(Spark::Event &event)
{
    Spark::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Spark::KeyPressedEvent>(std::bind(&LayerTest::HandleKeyInputEvents, this, std::placeholders::_1));

    auto entities = m_World->GetContext().view<Spark::CameraComponent>();
    for(auto e : entities)
    {
        Spark::CameraComponent& c = m_World->GetContext().get<Spark::CameraComponent>(e);
        c.OnEvent(event);
    }
}
// ------------------------------------------------

bool LayerTest::HandleKeyInputEvents(Spark::Event &event)
{
    return false;
}

} // namespace Sandbox