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

    void World::Update(Timestep dt)
    {
        auto& entities = m_Context.view<Component>();
        for(auto& e : entities)
        {
            Component& c = m_Context.get<Component>(e);
            c.Update(dt);
        }
    }

    entt::registry& World::GetContext()
    {
        return m_Context;
    }

    Ref<Level> World::GetCurrentLevel()
    {
        return m_Levels[m_ActiveSceneIndex];
    }


} // namespace Spark
