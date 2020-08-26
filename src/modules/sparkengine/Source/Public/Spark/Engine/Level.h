#pragma once

#include "Spark/Engine/World.h"
#include "entt.hpp" 
#include "Spark/Engine/GameFramework/Entity.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class World;
    class Entity;
    class SPARKENGINE_API Level : public Object
    {
    private:
        World* m_WorldRef;
        std::vector<Entity*> m_Entities;

    public:
        Level(World* WorldReference);
        ~Level();

        void Begin() {}
        void Update(Timestep ts);

        World* GetWotld();
        entt::registry& GetWorldContext();
        Entity& CreateEntity();

    };
} // namespace Spark
