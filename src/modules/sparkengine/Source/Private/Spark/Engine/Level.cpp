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
        return *(new Spark::Entity(GetWorldContext().create(), this));
    }

} // namespace Spark
