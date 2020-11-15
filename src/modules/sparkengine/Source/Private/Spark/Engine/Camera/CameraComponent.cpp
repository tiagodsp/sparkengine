#include "sparkengine.PCH.h"
#include "Spark/Engine/Camera/CameraComponent.h"
#include "Spark/Engine/Level.h"
#include "Spark/Engine/GameFramework/Entity.h"
#include "Spark/Core/Input.h"
#include "Spark/Core/KeyCodes.h"

namespace Spark
{
    CameraComponent::CameraComponent()
    {
        CORE_ASSERT(false, "Can not initialize camera without a default camera.");
    }
    
    CameraComponent::CameraComponent(Ref<Camera> camera)
            : m_Camera(camera)
    {}
    
    CameraComponent::~CameraComponent()
    {}

    void CameraComponent::Begin()
    {

    }

    void CameraComponent::Update(Timestep ts)
    {
        if(m_Parent->HasComponent<TransformComponent>())
        {
            auto t = m_Parent->GetComponent<TransformComponent>();
            
            if (Spark::Input::IsKeyPressed(SPARK_KEY_RIGHT))
                t->Position += glm::vec3(m_CameraSpeed * ts, 0, 0);
            else if (Spark::Input::IsKeyPressed(SPARK_KEY_LEFT))
                t->Position += glm::vec3(-m_CameraSpeed * ts, 0, 0);

            if (Spark::Input::IsKeyPressed(SPARK_KEY_UP))
                t->Position += glm::vec3(0, m_CameraSpeed * ts, 0);
            else if (Spark::Input::IsKeyPressed(SPARK_KEY_DOWN))
                t->Position += glm::vec3(0, -m_CameraSpeed * ts, 0);
            
            m_Camera->SetPosition(t->Position);
        }

        //m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
    }

    void CameraComponent::SetAspectRatio(float aspectRation)
    {
        m_AspectRatio = aspectRation;
        m_Camera->SetAspectRatio(m_AspectRatio);
    }

    void CameraComponent::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrollEvent>(std::bind(&CameraComponent::OnMouseScroll, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&CameraComponent::OnWindowsResize, this, std::placeholders::_1));
    }        

    bool CameraComponent::OnMouseScroll(MouseScrollEvent& e)
    {
        float zoom = (float)m_ZoomLevel + (float)e.GetYOffset();
        m_ZoomLevel = zoom > 1.0f ? zoom : 1.0f;
        // m_OrthoCamera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel , m_ZoomLevel);
        return true;
    }

    bool CameraComponent::OnWindowsResize(WindowResizeEvent& e)
    {
        //m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        //m_OrthoCamera->SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}

REFLECTION_CLASS_BEGIN(Spark::CameraComponent)
REFLECTION_CLASS_MEMBER(m_ZoomLevel)
REFLECTION_CLASS_MEMBER(m_AspectRatio)
REFLECTION_CLASS_END()