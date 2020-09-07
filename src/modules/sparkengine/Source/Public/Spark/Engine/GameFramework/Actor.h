#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Engine/Components/Component.h"
#include "Spark/Core/Timestep.h"
#include "Spark/Events/Event.h"

#include "Spark/Object/Object.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class TransformComponent : public Component
    {
    public:
        glm::mat4 Transform;
        
        TransformComponent()
            : Transform(glm::mat4(1.0f))
        {}
        TransformComponent(glm::mat4 Transform)
            : Transform(Transform)
        {}

        virtual void Begin() override {}
        virtual void Update(Timestep ts) override {}
        virtual void OnEvent(Event& e) override {}
    };
    
    
    class SPARKENGINE_API Actor : public Object
    {
    private:
        class Level* m_Level;
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
            m_Components.push_back(c);
            return *c;
        }

    };
} // namespace Spark
