#include "sparkengine.PCH.h"
#include "Spark/Engine/GameFramework/Entity.h"

namespace Spark
{
    Entity::Entity()
    {
    }

    Entity::Entity(entt::entity EntityHandle, Level* Level)
        : m_EntityHandle(EntityHandle)
        , m_Level(Level)
    {
    }

    Entity::~Entity()
    {
    }

    entt::registry& Entity::GetContext()
    {
        return m_Level->GetWorldContext();
    }

} // namespace Spark
