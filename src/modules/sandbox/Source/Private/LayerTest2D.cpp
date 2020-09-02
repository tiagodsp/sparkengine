#include "LayerTest2D.h"
#include "Spark/Renderer/Renderer2D.h"
#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Engine/Camera/CameraComponent.h"
#include "Spark/Core/Profiling.h"

namespace Sandbox
{
    LayerTest2D::LayerTest2D()
    {
        m_World = std::make_shared<Spark::World>();
    }
    
    LayerTest2D::~LayerTest2D()
    {
        
    }

    void LayerTest2D::OnAttach()
    {
        m_CameraActor = std::make_shared<Spark::Actor>(m_World->GetCurrentLevel());
        m_CameraActor->AddComponent<Spark::CameraComponent>();
        m_Texture = Spark::Texture2D::Create("Assets/Textures/digital.png");
    }
    
    void LayerTest2D::OnDetach()
    {

    }
    
    void LayerTest2D::OnUpdate(Spark::Timestep delta)
    {
        PROFILE_SCOPE("LayerTest2D::OnPudate");
        //Spark::Timer timer("LayerTest2D::OnPudate", [&](std::pair<const char*, long long> ProfileResult){ Spark::Profiler::Get().PushBack(ProfileResult.first, ProfileResult.second); });
        
        m_World->Update(delta);

        Spark::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Spark::RenderCommand::Clear();

        Spark::Renderer2D::BeginScene(*m_CameraActor->GetComponent<Spark::CameraComponent>()->GetOrthoCamera());
        
        Spark::Renderer2D::DrawQuad(glm::vec3({0.0f, 0.0f, 0.0f}), glm::vec2({1.0f, 1.0f}), glm::vec4({1.0f, 1.0f, 1.0f, 1.0f}), m_Texture);
        Spark::Renderer2D::DrawQuad(glm::vec3({0.1f, 0.0f, -0.1f}), glm::vec2({1.0f, 1.0f}), glm::vec4({1.0f, 0.0f, 0.0f, 1.0f}));
        
        Spark::Renderer2D::EndScene();
        
    }
    
    void LayerTest2D::OnEvent(Spark::Event& event)
    {
        m_World->OnEvent(event);
    }
} // namespace Sandbox
