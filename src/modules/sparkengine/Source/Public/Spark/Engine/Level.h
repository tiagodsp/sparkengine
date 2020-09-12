#pragma once

#include "Spark/Engine/Object/Object.h"
#include "Spark/Engine/GameFramework/EntityComponentManager.h"
#include "Spark/Events/Event.h"
#include "Spark/Engine/GameFramework/Actor.h"

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
        std::vector<Actor*> m_Actors;

    public:
        Level(World* WorldReference);
        ~Level();

        void Begin() {}
        void Update(Timestep ts);
        void OnEvent(Event& e);

        World* GetWotld();
        EntityComponentManager& GetWorldContext();
        void RegisterActor(Actor* Actor);
        const std::vector<Actor*>& GetActors() { return m_Actors; }

    };
} // namespace Spark
