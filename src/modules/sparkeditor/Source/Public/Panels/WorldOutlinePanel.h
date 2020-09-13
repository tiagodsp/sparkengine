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
            
            ImGuiTreeNodeFlags flags;
            flags |= ImGuiTreeNodeFlags_OpenOnArrow;
            flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;

            if(ImGui::TreeNode("World"))
            {
                for(auto& actor : actors)
                {
                    if(ImGui::TreeNodeEx(actor->StaticType.name, flags))
                    {
                        SelectionManager::Get().SetCurrentSelection(actor);        
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }
            ImGui::End();
        }
    };

}