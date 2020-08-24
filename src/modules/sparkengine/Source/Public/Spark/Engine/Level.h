#pragma once

#include "Spark/Engine/World.h"
#include "entt.hpp" 
#include "Spark/Engine/GameFramework/Entity.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class World;

    class SPARKENGINE_API Level : public Object
    {
    private:
        World* m_WorldRef;

    public:
        Level(World* WorldReference);
        ~Level();

        World* GetWotld();
        entt::registry& GetWorldContext();
        class Entity& CreateEntity();

    };
} // namespace Spark
