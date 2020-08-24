#pragma once

#include "Spark/Object/Object.h"
#include "Spark/Core/Timestep.h"
#include "Spark/Events/Event.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Component : public Object
    {
    private:
        /* data */
    public:
        Component(/* args */) {}
        ~Component() {}

        virtual void Begin() {}
        virtual void Update(Timestep ts) {}
        virtual void OnEvent(Event& e) {}
    };
} // namespace Spark
