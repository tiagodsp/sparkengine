#pragma once

#include "glm/glm.hpp"
#include "Spark/Engine/Components/ActorComponent.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API SceneComponent : public ActorComponent
    {
    private:
        glm::mat4 Transform;
    public:
        SceneComponent(/* args */) {}
        ~SceneComponent() {}
    };
} // namespace Spark
