#include "SelectionManager.h"

namespace Spark
{
    SelectionManager SelectionManager::s_Instance;

    void SelectionManager::SetCurrentSelection(Actor* selection)
    {
        m_CurrentSelection = selection;
        OnSelectionChange(selection);
    }

    Actor* SelectionManager::GetCurrentSelection()
    {
        return m_CurrentSelection;
    }

} // namespace Spark
