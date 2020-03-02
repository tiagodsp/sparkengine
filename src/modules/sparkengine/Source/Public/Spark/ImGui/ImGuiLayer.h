#pragma once

#include "sparkengine.PCH.h"
#include "Spark/Layer.h"
#include "Spark/Events/MouseEvent.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Events/KeyEvent.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        virtual ~ImGuiLayer();

        // Layer interface implementation ---------
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep delta) override;
        virtual void OnEvent(Event& event) override;
    
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseScrollEvent(MouseScrollEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnWindowResizedEvent(WindowResizeEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        
    private:
        float m_Time = 0.0f;
    };
}
