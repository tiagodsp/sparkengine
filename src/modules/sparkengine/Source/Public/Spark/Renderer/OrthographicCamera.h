#pragma once

#include "glm/glm.hpp"
#include "Spark/Renderer/Camera.h"
#include <sparkengine.api.gen.h>

namespace Spark
{

class SPARKENGINE_API OrthographicCamera : public Camera
{
private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };

    float m_AspectRation = 1.0f;
private:
    void RecalculateViewMatrix();
public:
    OrthographicCamera(float left, float right, float bottom, float top);
    virtual ~OrthographicCamera();

    void SetProjection(float left, float right, float bottom, float top);
    
    virtual void SetAspectRatio(float aspectRation) override { m_AspectRation = aspectRation; RecalculateViewMatrix(); };

    virtual const glm::vec3& GetPosition() const { return m_Position; }
    virtual void SetPosition(const glm::vec3 &position) { m_Position = position; RecalculateViewMatrix(); }

    virtual const glm::vec3& GetRotation() const  { return m_Rotation; }
    virtual void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

    virtual const glm::mat4& GetProjectionMatix() const  override { return m_ProjectionMatrix; }
    virtual const glm::mat4& GetViewMatrx() const  override { return m_ViewMatrix; }
    virtual const glm::mat4& GetViewProjectionMatix() const override { return m_ViewProjectionMatrix; }
};

} // namespace Spark
