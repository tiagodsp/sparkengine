#pragma once

#include "Spark/Renderer/Camera.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

    struct SPARKENGINE_API PerspectiveCameraParameters
    {
        float fov;
        float aspectRatio;
        float zNear;
        float zFar;
        
        PerspectiveCameraParameters(float fov, float aspectRation, float zNear, float zFar)
            : fov(fov), aspectRatio(aspectRatio), zNear(zNear), zFar(zFar)
        {}
    };

    class SPARKENGINE_API PerspectiveCamera : public Camera
    {
    private:
        PerspectiveCameraParameters m_Parameters;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position{0.0f, 0.0f, 0.0f};
        glm::vec3 m_Rotation{0.0f, 0.0f, 0.0f};

    private:
        void RecalculateViewMatrix();
    public:
        PerspectiveCamera(PerspectiveCameraParameters parameters);
        ~PerspectiveCamera();

        void SetProjection(PerspectiveCameraParameters parameters);

        virtual void SetAspectRatio(float aspectRation) override { m_Parameters.aspectRatio = aspectRation; RecalculateViewMatrix(); }

        const glm::vec3& GetPosition() const override { return m_Position; }
        void SetPosition(const glm::vec3& position) override { m_Position = position; RecalculateViewMatrix(); }

        const glm::vec3& GetRotation() const override { return m_Rotation; }
        void SetRotation(const glm::vec3& rotation) override { m_Rotation = rotation; RecalculateViewMatrix(); }

        virtual const glm::mat4 &GetProjectionMatix() const override { return m_ProjectionMatrix; };
        virtual const glm::mat4 &GetViewMatrx() const override { return m_ViewMatrix; };
        virtual const glm::mat4 &GetViewProjectionMatix() const override { return m_ViewProjectionMatrix; };
    };

} // namespace Spark