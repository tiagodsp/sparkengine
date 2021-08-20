#pragma once

#include "Spark/ImGui/ImGuiLayer.h"
#include "Spark/Events/MouseEvent.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Events/KeyEvent.h"

namespace Spark
{

/**
 * ImGuiLayer implementation for Metal Renderer;
 **/
class MetalImGuiLayer : public ImGuiLayer
{
  public:
	MetalImGuiLayer(/* args */);
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void Begin() override;
	virtual void End() override;
	virtual void OnImGuiRender(ImGuiContext *context) override;
	virtual void OnEvent(Event &event) override;
	ImGuiContext * GetImGuiContext() override { return m_Context; }

  private:
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
	bool OnMouseScrollEvent(MouseScrollEvent &e);
	bool OnMouseMovedEvent(MouseMovedEvent &e);
	bool OnWindowResizedEvent(WindowResizeEvent &e);
	bool OnKeyPressedEvent(KeyPressedEvent &e);
	bool OnKeyReleasedEvent(KeyReleasedEvent &e);
	bool OnKeyTypedEvent(KeyTypedEvent &e);

  private:
	float m_Time = 0.0f;
	ImGuiContext *m_Context;
};

} // namespace Spark