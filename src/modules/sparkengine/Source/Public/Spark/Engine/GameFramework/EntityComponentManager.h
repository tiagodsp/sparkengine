#pragma once


#include "Spark/CoreTypes.h"
#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include "Spark/Engine/Components/Component.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class Actor;
    
    constexpr std::size_t MaxComponents{32};
    using Entity = std::size_t;
    
    using ComponentBitset = std::bitset<MaxComponents>;
    using Pool = std::vector<Component*>;


    class SPARKENGINE_API EntityComponentManager
    {
    private:
        
        //m_EntityComponentsBitset - Stores if given entity has some component.
        // =======================
        // =     A   B   C   D...=
        // = c1  1   0   1   0...=
        // = c2  1   1   0   0...=
        // = c3  0   0   0   1...=
        // =======================
        std::vector<ComponentBitset> m_EntityComponentsBitset;
        
        //m_ComponentPoolArray - Stores the component reference for each entity.
        // =========================
        // =     A   B   C   D  ...=
        // = c1  ptr ptr ptr nul...=
        // = c2  ptr nul nul nul...=
        // = c3  nul ptr nul ptr...=
        // =========================
        std::array<Pool, MaxComponents> m_ComponentPoolArray;
        
        
        Entity m_LastID = -1;

    public:
        EntityComponentManager(/* args */){}
        ~EntityComponentManager() {}

        Entity Create()
        {
            m_EntityComponentsBitset.push_back(ComponentBitset());
            for(auto& pool : m_ComponentPoolArray)
                pool.push_back(nullptr);
            return ++m_LastID;
        }
        
        template<typename T>
        bool Has(Entity e)
        {
            return m_EntityComponentsBitset[e][GetComponentID<T>()];
        }
        
        template<typename T>
        T* Get(Entity e)
        {
            ASSERT(Has<T>(), "Actor does not have the requested component!");
            return m_ComponentPoolArray[GetComponentID<T>()][e];
        }
        
        template<typename T, typename... Args>
        T* Emplace(Entity e, Args&&... args)
        {
            CORE_ASSERT(!Has<T>(e), "Entity already contains this component!");
            T* c(new T(std::forward<Args>(args)...));
            m_ComponentPoolArray[GetComponentID<T>()][e] = c;
            return c;
        }

    };

} // namespace Spark
