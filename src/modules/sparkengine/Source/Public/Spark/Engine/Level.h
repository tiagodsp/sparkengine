#pragma once

#include "Spark/Object/Object.h"
#include "Spark/Engine/GameFramework/EntityComponentManager.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class World;
    class Timestep;
    class EntityComponentManager;

    class SPARKENGINE_API Level : public Object
    {
    private:
        World* m_WorldRef;
        std::vector<class Actor*> m_Actors;

    public:
        Level(World* WorldReference);
        ~Level();

        void Begin() {}
        void Update(Timestep ts);

        World* GetWotld();
        EntityComponentManager& GetWorldContext();
        void RegisterActor(Actor* Actor);

    };
} // namespace Spark
