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
#include "Spark/Engine/GameFramework/Actor.h"

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
    Spark::Actor* camera = new Spark::Actor(m_World->GetCurrentLevel());
    camera->AddComponent<Spark::TransformComponent>();
    camera->AddComponent<Spark::CameraComponent>(m_Camera);

    mesh = new Spark::Actor(m_World->GetCurrentLevel());
    mesh->AddComponent<Spark::TransformComponent>();
    mesh->AddComponent<Spark::MeshComponent>("./Assets/Meshes/monkey.glb");
    //mesh.AddComponent<Spark::MeshComponent>("E:/coffee.gltf");
    //mesh.AddComponent<Spark::MeshComponent>("E:/aquelamaquinala.glb");
    //mesh.AddComponent<Spark::MeshComponent>("E:/PowerSupply_glTF.glb");


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

    Spark::TransformComponent* t = mesh->GetComponent<Spark::TransformComponent>();
    Spark::MeshComponent* mc = mesh->GetComponent<Spark::MeshComponent>();
    m_Texture->Bind();
    for(auto& va : mc->GetVertexArrays())
    {
        Spark::Renderer::Submit(m_ShaderLibrary.Get("Texture"), va, t->Transform);
    }

    
    
    Spark::Renderer::EndScene();
}

void LayerTest::OnEvent(Spark::Event &event)
{
    Spark::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Spark::KeyPressedEvent>(std::bind(&LayerTest::HandleKeyInputEvents, this, std::placeholders::_1));

    m_World->OnEvent(event);
}
// ------------------------------------------------

bool LayerTest::HandleKeyInputEvents(Spark::Event &event)
{
    return false;
}

} // namespace Sandbox