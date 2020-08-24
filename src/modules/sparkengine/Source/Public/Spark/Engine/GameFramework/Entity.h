#pragma once

#include "Spark/CoreTypes.h"
#include "Spark/Engine/Components/Component.h"
#include "Spark/Core/Timestep.h"
#include "entt.hpp"
#include "Spark/Engine/Level.h"
#include "Spark/Object/Object.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Entity : public Object
    {
    private:
        entt::entity m_EntityHandle;
        class Level* m_Level;
        Ref<Component> RootComponent;

    public:
        Entity();
        Entity(entt::entity EntityHandle, Level* Level);
        ~Entity();

        virtual void Begin() {}
        virtual void Update(Timestep timestep) {}

        entt::registry& GetContext();

        template<typename T>
        bool HasComponent()
        {
            return GetContext().has<T>(m_EntityHandle);
        }

        template<typename T>
        T& GetComponent()
        {
            return GetContext().get<T>(m_EntityHandle);
        }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            return GetContext().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

    };
} // namespace Spark
