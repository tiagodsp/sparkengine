#pragma once

#include "Spark/Core/Delegate.h"
#include "Spark/Engine/GameFramework/Actor.h"
#include <map>

namespace Spark
{
    class SelectionManager
    {
    private:
        static SelectionManager s_Instance;
        Actor* m_CurrentSelection;
    public:
        static SelectionManager& Get() { return s_Instance; }
        void SetCurrentSelection(Actor* selection);

        Delegate<Actor*> OnSelectionChange;

    };
    
} // namespace Spark
