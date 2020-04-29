#pragma once

#include "Spark/CoreTypes.h"
#include "Spark/Layer.h"
#include "Spark/PlatformWindow.h"
#include "Spark/LayerStack.h"
#include "Spark/Renderer/IShader.h"
#include "Spark/Renderer/IBuffer.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/Renderer/RenderCommand.h"
#include "Spark/Renderer/OrthographicCamera.h"
#include "Spark/Events/Event.h"
#include "Spark/Log.h"

#include "sandbox.api.gen.h"

namespace Sandbox
{

class LayerTest : public Spark::Layer
{
private:
    Spark::Ref<Spark::IShader> m_Shader;
    Spark::Ref<Spark::IVertexBuffer> m_VertexBuffer;
    Spark::Ref<Spark::IIndexBuffer> m_IndexBuffer;
    Spark::Ref<Spark::IVertexArray> m_VertexArray;

    Spark::OrthographicCamera m_Camera = Spark::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
    float m_CameraSpeed = 1.0f;

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