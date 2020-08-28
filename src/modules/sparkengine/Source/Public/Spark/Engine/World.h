#pragma once

#include "Spark/CoreTypes.h"
#include "Spark/Object/Object.h"
#include "Spark/Engine/Level.h"
#include <vector>
#include "entt.hpp"
#include "Spark/Core/Timestep.h"
#include "Spark/Engine/GameFramework/EntityComponentManager.h"

#include "sparkengine.api.gen.h"

namespace Spark
{   
    class Level;
    
    class SPARKENGINE_API World : public Object
    {
    private:
        EntityComponentManager m_Context;
        std::vector<Ref<Level>> m_Levels;
        int32 m_ActiveSceneIndex;

    public:
        
        World();
        World(Ref<Level> PersistentLevel);
        ~World();

        void Update(Timestep ts);

        EntityComponentManager& GetContext();
        Level* GetCurrentLevel();
    };
} // namespace Spark   
