#pragma once

#include "Spark/Engine/Components/Component.h"
#include "Spark/Renderer/Camera.h"
#include "Spark/Events/MouseEvent.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Core/Reflection.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API CameraComponent : public Component
    {
        REFLECT_CLASS()
    private:
        float m_AspectRatio = 1.0f;
        float m_ZoomLevel = 1.0f;
        float m_CameraSpeed = 10.0f;
        Ref<Camera> m_Camera;
    public:        
        CameraComponent();
        CameraComponent(Ref<Camera> camera);
        ~CameraComponent();

        virtual void Begin() override;
        virtual void Update(Timestep ts) override;
        virtual void OnEvent(Event& e) override;

        void SetAspectRatio(float aspectRation);

        bool OnMouseScroll(MouseScrollEvent& e);
        bool OnWindowsResize(WindowResizeEvent& e);

        inline Ref<Camera> GetCamera() { return m_Camera; }

    };
} // namespace Spark

