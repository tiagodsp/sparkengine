#pragma once

#include "Spark/Object/Object.h"
#include "Spark/Core/Timestep.h"
#include "Spark/Events/Event.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API ActorComponent : public Object
    {
    private:
        /* data */
    public:
        ActorComponent(/* args */) {}
        ~ActorComponent() {}

        virtual void Begin() {}
        virtual void Update(Timestep ts) {}
        virtual void OnEvent(Event& e) {}
    };
} // namespace Spark
