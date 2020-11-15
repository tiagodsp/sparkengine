#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Core/Layer.h"
#include "Spark/Core/PlatformWindow.h"
#include "Spark/Core/LayerStack.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/IBuffer.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/OrthographicCamera.h"
#include "Spark/Events/Event.h"
#include "Spark/Core/Log.h"
#include "Spark/Renderer/Texture.h"
#include "Spark/Engine/World.h"
#include "Spark/Renderer/Framebuffer.h"

namespace Spark
{

    class SparkEditorLayer : public Layer
    {
    private:
        Ref<Entity> m_CameraActor;
        Ref<World> m_World;
        Ref<Texture> m_Texture;
        Ref<IFramebuffer> m_MainViewportFramebuffer;
        Ref<ShaderLibrary> m_ShaderLibrary;
        glm::vec2 m_ViewportSize;

    public:
        SparkEditorLayer();
        virtual ~SparkEditorLayer();

        // Spark::Layer interface implementation ---------
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep delta) override;
        virtual void OnImGuiRender(ImGuiContext* context) override;
        virtual void OnEvent(Event &event) override;
        // ------------------------------------------------

        //TO DELETE
        void SparkEditorLayer::Hue(Entity* ref);

    private:
        bool HandleKeyInputEvents(Event &event);
    };

} // namespace Spark