#include "SparkEditorLayer.h"

#include "Spark/Events/KeyEvent.h"
#include "Spark/Core/KeyCodes.h"
#include "Spark/Core/Input.h"
#include "Spark/Core/GenericPlatform/GenericPlatformFile.h"
#include "Spark/Core/Misc/Paths.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Spark/Engine/World.h"
#include "Spark/Engine/Camera/CameraComponent.h"
#include "Spark/Engine/Mesh/MeshComponent.h"
#include "Spark/Engine/GameFramework/Actor.h"
#include "Spark/Renderer/Renderer2D.h"
#include "Spark/Core/Profiling.h"
#include "imgui.h"

DECLARE_LOG_CATEGORY(LayerTest);

namespace Spark
{

    SparkEditorLayer::SparkEditorLayer()
    {
        m_World.reset<Spark::World>(new Spark::World());
    }

    SparkEditorLayer::~SparkEditorLayer()
    {
    }

    // Spark::Layer interface implementation ---------

    void SparkEditorLayer::OnAttach()
    {
        m_CameraActor = std::make_shared<Spark::Actor>(m_World->GetCurrentLevel());
        m_CameraActor->AddComponent<Spark::CameraComponent>();
        m_Texture = Spark::Texture2D::Create("Assets/Textures/digital.png");
    }

    void SparkEditorLayer::OnDetach()
    {
    }

    void SparkEditorLayer::OnUpdate(Spark::Timestep delta)
    {
        PROFILE_SCOPE("LayerTest2D::OnPudate");
        //Spark::Timer timer("LayerTest2D::OnPudate", [&](std::pair<const char*, long long> ProfileResult){ Spark::Profiler::Get().PushBack(ProfileResult.first, ProfileResult.second); });

        m_World->Update(delta);

        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        RenderCommand::Clear();

        Renderer2D::BeginScene(*m_CameraActor->GetComponent<CameraComponent>()->GetOrthoCamera());

        Renderer2D::DrawQuad(glm::vec3({0.0f, 0.0f, 0.0f}), glm::vec2({1.0f, 1.0f}), glm::vec4({1.0f, 1.0f, 1.0f, 1.0f}), m_Texture);
        Renderer2D::DrawQuad(glm::vec3({0.1f, 0.0f, -0.1f}), glm::vec2({1.0f, 1.0f}), glm::vec4({1.0f, 0.0f, 0.0f, 1.0f}));

        Renderer2D::EndScene();
    }

    void SparkEditorLayer::OnImGuiRender(ImGuiContext* context)
    {
        ImGui::SetCurrentContext(context);
        ImGui::Begin("Test");
        ImGui::Text("HUEEEEE");
        ImGui::End();
    }

    void SparkEditorLayer::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&SparkEditorLayer::HandleKeyInputEvents, this, std::placeholders::_1));

        m_World->OnEvent(event);
    }
    // ------------------------------------------------

    bool SparkEditorLayer::HandleKeyInputEvents(Event &event)
    {
        return false;
    }

} // namespace Spark