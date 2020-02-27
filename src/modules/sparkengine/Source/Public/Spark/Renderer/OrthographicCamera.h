#pragma once

#include "glm/glm.hpp"

#include <sparkengine.api.gen.h>

namespace Spark
{

class SPARKENGINE_API OrthographicCamera
{
private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    float m_Rotation = 0.0f;

private:
    void RecalculateViewMatrix();
public:
    OrthographicCamera(float left, float right, float bottom, float top);
    virtual ~OrthographicCamera();

    inline const glm::vec3& GetPosition() const { return m_Position; }
    inline void SetPosition(const glm::vec3 &position) { m_Position = position; RecalculateViewMatrix(); }

    inline float GetRotation() const { return m_Rotation; }
    inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

    inline const glm::mat4& GetProjectionMatix() const { return m_ProjectionMatrix; }
    inline const glm::mat4& GetViewMatrx() const { return m_ViewMatrix; }
    inline const glm::mat4& GetViewProjectionMatix() const { return m_ViewProjectionMatrix; }
};

} // namespace Spark
