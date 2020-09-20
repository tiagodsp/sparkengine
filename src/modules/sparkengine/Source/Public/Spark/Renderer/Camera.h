#pragma once

#include "Spark/Engine/Object/Object.h"
#include "glm/glm.hpp"
#include "sparkengine.api.gen.h"

namespace Spark
{

    class Camera
    {
    public:
        virtual void SetAspectRatio(float aspectRation) = 0;

        virtual const glm::vec3& GetPosition() const = 0 ;
        virtual void SetPosition(const glm::vec3& position) = 0;

        virtual const glm::vec3& GetRotation() const = 0;
        virtual void SetRotation(const glm::vec3& rotation) = 0;
        
        virtual const glm::mat4 &GetProjectionMatix() const = 0;
        virtual const glm::mat4 &GetViewMatrx() const = 0;
        virtual const glm::mat4 &GetViewProjectionMatix() const = 0;
    };

} // namespace Spark
