#include "sparkengine.PCH.h"
#include "Spark/Engine/Camera/CameraComponent.h"

#include "Spark/Input.h"
#include "Spark/KeyCodes.h"

namespace Spark
{
    CameraComponent::CameraComponent(OrthographicCamera& orthoCamera)
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
            m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() + glm::vec3(m_CameraSpeed * ts, 0, 0));
        else if (Spark::Input::IsKeyPressed(SPARK_KEY_LEFT))
            m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() + glm::vec3(-m_CameraSpeed * ts, 0, 0));

        if (Spark::Input::IsKeyPressed(SPARK_KEY_UP))
            m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() + glm::vec3(0, m_CameraSpeed * ts, 0));
        else if (Spark::Input::IsKeyPressed(SPARK_KEY_DOWN))
            m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() + glm::vec3(0, -m_CameraSpeed * ts, 0));
    }

    void CameraComponent::OnEvent(Event& e)
    {

    }
}