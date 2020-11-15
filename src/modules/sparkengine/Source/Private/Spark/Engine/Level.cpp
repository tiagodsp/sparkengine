#include "sparkengine.PCH.h"
#include "Spark/Engine/Level.h"
#include "Spark/Engine/World.h"

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
        for(auto& a : m_Entities) a->Update(ts);
    }

    void Level::OnEvent(Event& e)
    {
        for(auto& a : m_Entities) a->OnEvent(e);
    }

    World* Level::GetWotld()
    {
        return m_WorldRef;
    }
    
    EntityComponentManager& Level::GetWorldContext()
    {
        return GetWotld()->GetContext();
    }

    void Level::RegisterEntity(Entity* Entity)
    {
        m_Entities.push_back(Entity);
    }



} // namespace Spark
