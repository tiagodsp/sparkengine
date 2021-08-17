#include "sparkengine.PCH.h"
#include "Spark/Renderer/PerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"


namespace Spark
{
    PerspectiveCamera::PerspectiveCamera(PerspectiveCameraParameters parameters)
        : m_Parameters(parameters)
    {
        SetProjection(m_Parameters);
    }
    
    void PerspectiveCamera::SetProjection(PerspectiveCameraParameters parameters)
    {
        m_ProjectionMatrix = glm::perspective(parameters.fov, parameters.aspectRatio, parameters.zNear, parameters.zFar);
        RecalculateViewMatrix();
    }

    PerspectiveCamera::~PerspectiveCamera()
    {
    }

    void PerspectiveCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform(1.0f);
        //transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0));
        //transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0));
        //transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));
        transform *= glm::translate(glm::mat4(1.0f), m_Position);

        m_ProjectionMatrix = glm::perspective(glm::radians(m_Parameters.fov), m_Parameters.aspectRatio, m_Parameters.zNear, m_Parameters.zFar);
        m_ViewMatrix = transform;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
} // namespace Spark
