#pragma once

#include "Spark/Engine/Object/Object.h"
#include "Spark/Events/Event.h"
// #include "Spark/Engine/GameFramework/Entity.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class World;
    class Timestep;
    class EntityComponentManager;
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
        void OnEvent(Event& e);

        World* GetWotld();
        EntityComponentManager& GetWorldContext();
        void RegisterEntity(Entity* Entity);
        const std::vector<Entity*>& GetEntities() { return m_Entities; }

    };
} // namespace Spark
