#include "SparkEditorLayer.h"

#include "Spark/Events/KeyEvent.h"
#include "Spark/Core/KeyCodes.h"
#include "Spark/Core/Input.h"
#include "Spark/Core/GenericPlatform/GenericPlatformFile.h"
#include "Spark/Core/Misc/Paths.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Spark/Engine/World.h"
#include "Spark/Engine/Camera/CameraComponent.h"
#include "Spark/Renderer/PerspectiveCamera.h"
#include "Spark/Engine/Mesh/MeshComponent.h"
#include "Spark/Engine/GameFramework/Entity.h"
#include "Spark/Renderer/Renderer2D.h"
#include "Spark/Core/Profiling.h"
#include "imgui.h"
#include "Spark/Core/Application.h"
#include "EditField/DefaultEditField.h"
#include "SelectionManager.h"

// Panels ------
#include "Panels/WorldOutlinePanel.h"
#include "Panels/DetailsPanel.h"

DECLARE_LOG_CATEGORY(LayerTest);

namespace Spark
{

    SparkEditorLayer::SparkEditorLayer()
    {
        //m_World.reset<Spark::World>(new Spark::World());
        
        FramebufferProperties props;        
        props.Size = { Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight() };
        m_MainViewportFramebuffer = IFramebuffer::Create(props);
    }

    SparkEditorLayer::~SparkEditorLayer()
    {
    }

    // Spark::Layer interface implementation ---------

    void SparkEditorLayer::Hue(Entity* ref)
    {
        CORE_LOGI(ref->StaticType.name);
    }
    
    void SparkEditorLayer::OnAttach()
    {
        m_ShaderLibrary.reset(new ShaderLibrary());
        
        Entity* actorobj = (Entity*) NewObject("Spark::Entity");
        m_CameraActor.reset(actorobj);
        m_CameraActor->AddComponent<TransformComponent>();
        PerspectiveCameraParameters params(45.0f, 16.0f/9.0f, 1.0f, -1000.0f);
        m_CameraActor->AddComponent<CameraComponent>(std::make_shared<PerspectiveCamera>(params));
        //m_CameraActor->AddComponent<CameraComponent>(std::make_shared<OrthographicCamera>(-100,100,-100,100));

        //m_Texture = Spark::Texture2D::Create("Assets/Textures/digital.png");

        SelectionManager::Get().OnSelectionChange.Add(this, &SparkEditorLayer::Hue);

        Entity* mesh = (Entity*) NewObject("Spark::Entity");
        //mesh->AddComponent<MeshComponent>("E:/aquelamaquinala.glb");
        mesh->AddComponent<MeshComponent>("./Assets/Meshes/monkey.glb");
        mesh->AddComponent<TransformComponent>();
        auto texshader = m_ShaderLibrary->Load("./Assets/Shaders/TextureMesh.glsl");

        m_Texture = Spark::Texture2D::Create("./Assets/Textures/UV_Grid_Sm.jpg");
        texshader->Bind();
        texshader->UploadUniformInt("u_Texture", 0);



    }

    void SparkEditorLayer::OnDetach()
    {
    }

    void SparkEditorLayer::OnUpdate(Spark::Timestep delta)
    {
        PROFILE_FUNCTION();

        GWorld->Update(delta);

        m_MainViewportFramebuffer->Bind();
        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        RenderCommand::Clear();

        Renderer::BeginScene(*m_CameraActor->GetComponent<CameraComponent>()->GetCamera());

        GWorld->GetContext().Each<MeshComponent>([&](EntityID e, MeshComponent* meshComponent){
            auto transform = GWorld->GetContext().Get<TransformComponent>(e);
            m_Texture->Bind();
            for(auto va : meshComponent->GetVertexArrays())
                Renderer::Submit(m_ShaderLibrary->Get("TextureMesh"), va, transform->GetMatrix());
            m_Texture->Unbind();
        });

        //Renderer2D::DrawQuad(glm::vec3({0.0f, 0.0f, 0.0f}), glm::vec2({1.0f, 1.0f}), glm::vec4({1.0f, 1.0f, 1.0f, 1.0f}), m_Texture);
        //Renderer2D::DrawQuad(glm::vec3({0.1f, 0.0f, -0.1f}), glm::vec2({1.0f, 1.0f}), glm::vec4({1.0f, 0.0f, 0.0f, 1.0f}));

        Renderer::EndScene();
        m_MainViewportFramebuffer->Unbind();
    }

    void SparkEditorLayer::OnImGuiRender(ImGuiContext* context)
    {
        ImGui::SetCurrentContext(context);
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        ImGui::PopStyleVar();

        // DockSpace
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));

        // Main menu bar -----------------------------------------------------
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New")) {}
                if (ImGui::MenuItem("Open")) {}  // Disabled item
                if (ImGui::MenuItem("Save")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Preferences")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        
        // Viewport ---------------------------------------------------------------------
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0,0});
        ImGui::Begin("Viewport");
        ImVec2 regionAvail = ImGui::GetContentRegionAvail();
        if(m_ViewportSize != *(glm::vec2*)&regionAvail) // Check if the viewport size changed.
        {
            // Resize viewport and framebuffers.
            m_ViewportSize = {regionAvail.x, regionAvail.y};
            m_MainViewportFramebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);
            m_CameraActor->GetComponent<CameraComponent>()->SetAspectRatio(m_ViewportSize.x / m_ViewportSize.y);
        }
        uint32 texid = m_MainViewportFramebuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)texid, ImVec2{m_ViewportSize.x , m_ViewportSize.y}, ImVec2{0,1}, ImVec2{1,0}); // Set the viewport image
        ImGui::End();
        ImGui::PopStyleVar();
        // -------------------------------------------------------------------------------

        // Stats -------------------------------------------------------------------------
        ImGui::Begin("Stats");
        for(auto r : Profiler::Get().GetResults())
        {
            std::ostringstream ss;
            ss << r.first << " : " << r.second / (float)1000 << " ms" ;
            ImGui::Text(ss.str().c_str());
        }
        ImGui::End();
        // -------------------------------------------------------------------------------

        // World outline ----------------------------------------------------------------
        WorldOutlinePanel().OnGUI();
        // ------------------------------------------------------------------------------

        // Test Reflection ----------------------------------------------------------------
        DetailsPanel().OnGUI();
        // ------------------------------------------------------------------------------

        
        ImGui::End();
        ImGui::PopStyleVar();
        ImGui::PopStyleVar();

        ImGui::ShowDemoWindow();
    }

    void SparkEditorLayer::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&SparkEditorLayer::HandleKeyInputEvents, this, std::placeholders::_1));

        GWorld->OnEvent(event);
    }
    // ------------------------------------------------

    bool SparkEditorLayer::HandleKeyInputEvents(Event &event)
    {
        return false;
    }

} // namespace Spark