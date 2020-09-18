#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Engine/Components/Component.h"
#include "Spark/Core/Timestep.h"
#include "Spark/Events/Event.h"

#include "Spark/Engine/Object/Object.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API TransformComponent : public Component
    {
        REFLECT_CLASS()
    public:
        glm::vec3 Position;
        glm::vec3 Rotation;
        glm::vec3 Scale{1,1,1};

        glm::mat4 GetMatrix()
        {
            glm::mat4 matrix(1.0f);
            matrix *= glm::rotate(glm::radians(Rotation.x), glm::vec3( 1, 0, 0 ));
            matrix *= glm::rotate(glm::radians(Rotation.y), glm::vec3( 0, 1, 0 ));
            matrix *= glm::rotate(glm::radians(Rotation.z), glm::vec3( 0, 0, 1 ));
            matrix *= glm::scale(Scale);
            return glm::translate(matrix, Position);
        }
    };
    
    
    class Level;

    class SPARKENGINE_API Actor : public Object
    {
        REFLECT_CLASS()
    private:
        Level* m_Level;
        size_t m_EntityHandle;

    public:
        std::vector<Component*> m_Components;
        Actor();
        Actor(Level* Level);
        ~Actor();

        virtual void Begin() {}
        virtual void Update(Timestep ts);
        virtual void OnEvent(Event& e);

        template<typename T>
        bool HasComponent()
        {
            return m_Level->GetWorldContext().Has<T>(m_EntityHandle);
        }

        template<typename T>
        T* GetComponent()
        {
            return m_Level->GetWorldContext().Get<T>(m_EntityHandle);
        }

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            T* c = m_Level->GetWorldContext().Emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            CORE_ASSERT(dynamic_cast<Component*>(c) != nullptr, "Class is not a valid Component class!");
            c->m_Parent = this;
            m_Components.push_back(c);
            return *c;
        }

    };
} // namespace Spark
