#pragma once

#include "Spark/CoreTypes.h"
#include "Spark/Engine/Components/Component.h"
#include "Spark/Core/Timestep.h"
#include "entt.hpp"
#include "Spark/Engine/Level.h"
#include "Spark/Object/Object.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class TransformComponent : Component
    {
    public:
        glm::mat4 Transform;
        
        TransformComponent()
            : Transform(glm::mat4(1.0f))
        {}
        TransformComponent(glm::mat4 Transform)
            : Transform(Transform)
        {}
    };
    
    
    class SPARKENGINE_API Entity : public Object
    {
    private:
        TransformComponent* m_Tranform;
        entt::entity m_EntityHandle;
        class Level* m_Level;
        std::vector<Component*> m_Components;

    public:
        Entity();
        Entity(entt::entity EntityHandle, Level* Level);
        ~Entity();

        virtual void Begin() {}
        virtual void Update(Timestep ts)
        {
            for(auto& c : m_Components) c->Update(ts);
            glm::mat4 rot = glm::rotate(1.0f, glm::vec3(0,0,1));
            m_Tranform->Transform *= rot;
        }

        entt::registry& GetContext();

        template<typename T>
        bool HasComponent()
        {
            return GetContext().has<T>(m_EntityHandle);
        }

        template<typename T>
        T& GetComponent()
        {
            return GetContext().get<T>(m_EntityHandle);
        }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            T& c = GetContext().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            //m_Components.push_back(&c);
            
            return c;
        }

    };
} // namespace Spark
