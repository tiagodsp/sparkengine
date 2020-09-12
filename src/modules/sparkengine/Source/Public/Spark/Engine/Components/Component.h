#pragma once

#include "Spark/Engine/Object/Object.h"
#include "Spark/Core/Timestep.h"
#include "Spark/Events/Event.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    inline size_t GetComponentID()
    {
        static size_t lastId{0u};
        return lastId++;
    }

    template<typename T>
    size_t GetComponentID() noexcept
    {
        static size_t typeID{GetComponentID()};
        return typeID;
    }

    class SPARKENGINE_API Component : public Object
    {
    public:
        class Actor* m_Parent;
    public:
        
        Component(/* args */) {}
        ~Component() {}

        virtual void Begin() {}
        virtual void Update(Timestep ts) {}
        virtual void OnEvent(Event& e) {}
    };
} // namespace Spark
