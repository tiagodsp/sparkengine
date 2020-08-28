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
        for(auto& a : m_Actors) a->Update(ts);
    }

    void Level::OnEvent(Event& e)
    {
        for(auto& a : m_Actors) a->OnEvent(e);
    }

    World* Level::GetWotld()
    {
        return m_WorldRef;
    }
    
    EntityComponentManager& Level::GetWorldContext()
    {
        return GetWotld()->GetContext();
    }

    void Level::RegisterActor(Actor* Actor)
    {
        m_Actors.push_back(Actor);
    }



} // namespace Spark
