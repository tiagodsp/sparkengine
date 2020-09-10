#pragma once

#include "Spark/Engine/Components/Component.h"
#include "Spark/Renderer/OrthographicCamera.h"
#include "Spark/Events/MouseEvent.h"
#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Core/Reflection.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API CameraComponent : public Component
    {
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        float m_CameraSpeed = 10.0f;
        Ref<OrthographicCamera> m_OrthoCamera;
    public:
        CameraComponent(float AspectRation = 16.0f/9.0f);
        CameraComponent(Ref<OrthographicCamera> orthoCamera);
        ~CameraComponent();

        virtual void Begin() override;
        virtual void Update(Timestep ts) override;
        virtual void OnEvent(Event& e) override;

        bool OnMouseScroll(MouseScrollEvent& e);
        bool OnWindowsResize(WindowResizeEvent& e);

        inline Ref<OrthographicCamera> GetOrthoCamera() { return m_OrthoCamera; }

        REFLECT()
    };
} // namespace Spark

