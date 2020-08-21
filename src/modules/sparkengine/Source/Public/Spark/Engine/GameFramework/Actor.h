#pragma once

#include "Spark/CoreTypes.h"
#include "Spark/Engine/Components/ActorComponent.h"
#include "Spark/Core/Timestep.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Actor : public Object
    {
    protected:
        Ref<ActorComponent> RootComponent;

    public:
        Actor(/* args */) {}
        ~Actor() {}

        virtual void Begin() {}
        virtual void Update(Timestep timestep) {}

    };
} // namespace Spark
