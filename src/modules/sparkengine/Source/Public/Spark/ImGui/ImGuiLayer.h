#pragma once

#include "sparkengine.PCH.h"
#include "Spark/Core/Layer.h"
#include "Spark/Events/MouseEvent.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Events/KeyEvent.h"
#include "imgui.h"
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
        //virtual void OnUpdate(Timestep delta) override;
        virtual void OnImGuiRender(ImGuiContext* context) override;
        virtual void OnEvent(Event& event) override;

        void Begin();
        void End();
        ImGuiContext* GetImGuiContext() { return m_Context; }
    
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
        ImGuiContext* m_Context;
    };
}
