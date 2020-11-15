#include "sparkengine.PCH.h"
#include "Spark/Engine/GameFramework/Entity.h"
#include "Spark/Engine/Level.h"
#include "Spark/Engine/Camera/CameraComponent.h"
#include "Spark/Engine/World.h"

REFLECTION_CLASS_BEGIN(Spark::TransformComponent)
REFLECTION_CLASS_MEMBER(Position)
REFLECTION_CLASS_MEMBER(Rotation)
REFLECTION_CLASS_MEMBER(Scale)
REFLECTION_CLASS_END()

REFLECTION_CLASS_BEGIN(Spark::Entity)
REFLECTION_CLASS_END()

namespace Spark
{

    Entity::Entity()
        : m_Level(GWorld->GetCurrentLevel())
    {
        m_EntityHandle = m_Level->GetWorldContext().Create();
        m_Level->RegisterEntity(this);
    }

    Entity::Entity(Level* Level)
        : m_Level(Level)
    {
        m_EntityHandle = m_Level->GetWorldContext().Create();
        m_Level->RegisterEntity(this);
    }

    Entity::~Entity()
    {
    }

    void Entity::Update(Timestep ts)
    {
        for(auto c : m_Components) c->Update(ts);
        
        // if(HasComponent<TransformComponent>())
        // {
        //     auto& t = GetComponent<TransformComponent>();
        //     glm::mat4 rot = glm::rotate(1.0f * ts.GetTimeSeconds(), glm::vec3(1,0,0));
        //     t.Transform *= rot;
        // }
        // if(HasComponent<CameraComponent>())
        // {
        //     auto& t = GetComponent<CameraComponent>();
        //     t.Update(ts);
        // }
    }

    void Entity::OnEvent(Event& e)
    {
        for(auto c : m_Components) c->OnEvent(e);
    }

} // namespace Spark
