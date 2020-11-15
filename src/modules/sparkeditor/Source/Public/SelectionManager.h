#pragma once

#include "Spark/Core/Delegate.h"
#include "Spark/Engine/GameFramework/Entity.h"
#include <map>

namespace Spark
{
    class SelectionManager
    {
    private:
        static SelectionManager s_Instance;
        Entity* m_CurrentSelection;
    public:
        static SelectionManager& Get() { return s_Instance; }
        void SetCurrentSelection(Entity* selection);
        Entity* GetCurrentSelection();

        Delegate<Entity*> OnSelectionChange;

    };
    
} // namespace Spark
