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
    std::shared_ptr<Spark::IShader> m_Shader;
    std::shared_ptr<Spark::IVertexBuffer> m_VertexBuffer;
    std::shared_ptr<Spark::IIndexBuffer> m_IndexBuffer;
    std::shared_ptr<Spark::IVertexArray> m_VertexArray;

    int32 rotation_degrees = 0.0f;

    Spark::OrthographicCamera m_Camera = Spark::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
    float m_CameraSpeed = 0.1f;

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