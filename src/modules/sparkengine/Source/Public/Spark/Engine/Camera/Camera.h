#pragma once

#include "Spark/Engine/GameFramework/Entity.h"
#include "Spark/Engine/Camera/CameraComponent.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Camera : public Entity
    {
    private:
        Ref<CameraComponent> m_Camera;
    public:
        Camera();
        ~Camera();

        // virtual void Begin() override {}
        // virtual void Update(Timestep timestep) override {}
    };
} // namespace Spark
