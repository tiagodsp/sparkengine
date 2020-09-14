#pragma once

#include "Spark.h"
#include "SelectionManager.h"

namespace Spark
{
    class WorldOutlinePanel
    {
    public:
        void OnGUI()
        {
            ImGui::Begin("World Outliner");
            auto& actors = GWorld->GetCurrentLevel()->GetActors();
            
            for(auto& actor : actors)
            {
                ImGuiTreeNodeFlags flags = 0;
                flags |= (SelectionManager::Get().GetCurrentSelection() == actor) ?  ImGuiTreeNodeFlags_Selected : 0;
                flags |= ImGuiTreeNodeFlags_OpenOnArrow;
                //flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
                bool itemExpanded = ImGui::TreeNodeEx((void*)actor, flags, actor->StaticType.name);
                if(ImGui::IsItemClicked())
                {
                    SelectionManager::Get().SetCurrentSelection(actor);
                }
                if(itemExpanded)
                {
                    ImGui::TreePop();
                }
            }
            
            ImGui::End();
        }
    };

}