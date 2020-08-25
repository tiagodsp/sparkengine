#include "sparkengine.PCH.h"
#include "Spark/Engine/Camera/CameraComponent.h"

#include "Spark/Input.h"
#include "Spark/KeyCodes.h"

namespace Spark
{
    CameraComponent::CameraComponent()
        : m_OrthoCamera(std::make_shared<OrthographicCamera>(1.6f, 1.6f, 0.9f, 0.9f))
    {}
    
    CameraComponent::CameraComponent(Ref<OrthographicCamera> orthoCamera)
            : m_OrthoCamera(orthoCamera)
    {}
    
    CameraComponent::~CameraComponent()
    {}

    void CameraComponent::Begin()
    {

    }

    void CameraComponent::Update(Timestep ts)
    {
        if (Spark::Input::IsKeyPressed(SPARK_KEY_RIGHT))
            m_OrthoCamera->SetPosition(m_OrthoCamera->GetPosition() + glm::vec3(m_CameraSpeed * ts, 0, 0));
        else if (Spark::Input::IsKeyPressed(SPARK_KEY_LEFT))
            m_OrthoCamera->SetPosition(m_OrthoCamera->GetPosition() + glm::vec3(-m_CameraSpeed * ts, 0, 0));

        if (Spark::Input::IsKeyPressed(SPARK_KEY_UP))
            m_OrthoCamera->SetPosition(m_OrthoCamera->GetPosition() + glm::vec3(0, m_CameraSpeed * ts, 0));
        else if (Spark::Input::IsKeyPressed(SPARK_KEY_DOWN))
            m_OrthoCamera->SetPosition(m_OrthoCamera->GetPosition() + glm::vec3(0, -m_CameraSpeed * ts, 0));

        m_OrthoCamera->SetProjection(-1* m_ZoomLevel, 1* m_ZoomLevel, -1* m_ZoomLevel, 1* m_ZoomLevel);
    }

    void CameraComponent::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrollEvent>(std::bind(&CameraComponent::OnMouseScroll, this, std::placeholders::_1));
    }        

    bool CameraComponent::OnMouseScroll(MouseScrollEvent& e)
    {
        int zoom = m_ZoomLevel + e.GetYOffset();
        m_ZoomLevel = zoom > 0 ? zoom : 0;
        return true;
    }
}