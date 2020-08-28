#include "sparkengine.PCH.h"
#include "Spark/Engine/World.h"

namespace Spark
{
    World::World()
    {
        m_Levels.push_back(std::make_shared<Level>(this));
        m_ActiveSceneIndex = 0;
    }

    World::World(Ref<Level> PersistentLevel)
    {
        m_Levels.push_back(PersistentLevel);
        m_ActiveSceneIndex = 0;
    }
    
    World::~World()
    {
    }

    void World::Update(Timestep ts)
    {
        for(auto& level : m_Levels) level->Update(ts);
    }

    EntityComponentManager& World::GetContext()
    {
        return m_Context;
    }

    Level* World::GetCurrentLevel()
    {
        return &*m_Levels[m_ActiveSceneIndex];
    }

    void World::OnEvent(Event& e)
    {
        for(auto& level : m_Levels) level->OnEvent(e);
    }

} // namespace Spark
