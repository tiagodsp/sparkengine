#include "sparkengine.PCH.h"
#include "Spark/Engine/GameFramework/Entity.h"
#include "Spark/Engine/Level.h"
#include "Spark/Engine/Camera/CameraComponent.h"

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

    void Entity::Update(Timestep ts)
    {
        //for(auto c : m_Components) c->Update(ts);
        if(HasComponent<TransformComponent>())
        {
            auto& t = GetComponent<TransformComponent>();
            glm::mat4 rot = glm::rotate(1.0f * ts.GetTimeSeconds(), glm::vec3(1,0,0));
            t.Transform *= rot;
        }
        if(HasComponent<CameraComponent>())
        {
            auto& t = GetComponent<CameraComponent>();
            t.Update(ts);
        }
    }

    entt::registry& Entity::GetContext()
    {
        return m_Level->GetWorldContext();
    }

} // namespace Spark
