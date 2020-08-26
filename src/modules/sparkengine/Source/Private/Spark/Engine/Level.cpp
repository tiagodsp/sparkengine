#include "sparkengine.PCH.h"
#include "Spark/Engine/Level.h"

namespace Spark
{
    Level::Level(World* WorldReference)
        : m_WorldRef(WorldReference)
    {
    }
    
    Level::~Level()
    {
    }

    void Level::Update(Timestep ts)
    {
        for(auto& e : m_Entities) e->Update(ts);
    }

    World* Level::GetWotld()
    {
        return m_WorldRef;
    }
    
    entt::registry& Level::GetWorldContext()
    {
        return m_WorldRef->GetContext();
    }

    Entity& Level::CreateEntity()
    {
        Entity* entity = new Spark::Entity(GetWorldContext().create(), this);
        m_Entities.push_back(entity);
        return *entity;
    }

} // namespace Spark
