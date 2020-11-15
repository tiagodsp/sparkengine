#include "SelectionManager.h"

namespace Spark
{
    SelectionManager SelectionManager::s_Instance;

    void SelectionManager::SetCurrentSelection(Entity* selection)
    {
        m_CurrentSelection = selection;
        OnSelectionChange(selection);
    }

    Entity* SelectionManager::GetCurrentSelection()
    {
        return m_CurrentSelection;
    }

} // namespace Spark
