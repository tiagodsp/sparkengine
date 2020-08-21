#pragma once

#include "Spark/Engine/GameFramework/Actor.h"
#include "Spark/Engine/Camera/CameraComponent.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API CameraActor : public Actor
    {
    private:
        Ref<CameraComponent> m_Camera;
    public:
        CameraActor();
        ~CameraActor();

        virtual void Begin() override {};
        virtual void Update(Timestep timestep) override {};
    };
} // namespace Spark
