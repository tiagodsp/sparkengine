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

#include "sandbox.api.gen.h"

namespace Sandbox
{

class LayerTest : public Spark::Layer
{
private:
    Spark::ShaderLibrary m_ShaderLibrary;
    Spark::Ref<Spark::Texture2D> m_Texture, m_AlphaTexture;
    Spark::Ref<Spark::World> m_World;
    
    Spark::Actor* mesh;
    
    Spark::Ref<Spark::OrthographicCamera> m_Camera;

public:
    LayerTest();
    virtual ~LayerTest();

    // Spark::Layer interface implementation ---------
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Spark::Timestep delta) override;
    virtual void OnEvent(Spark::Event &event) override;
    // ------------------------------------------------
private:
    bool HandleKeyInputEvents(Spark::Event& event);
};

} // namespace Sandbox