#include "sparkengine.PCH.h"
#include "Spark/Renderer/OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Spark
{
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ViewMatrix(1.0f)
{
    SetProjection(left, right, bottom, top);
}

OrthographicCamera::~OrthographicCamera()
{

}

void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -100.0f, 100.0f);
    RecalculateViewMatrix();
}

void OrthographicCamera::RecalculateViewMatrix()
{
    glm::mat4 transform(1.0f);
    transform *= glm::translate(glm::mat4(1.0f), m_Position);
    transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

}

} // namespace Spark
