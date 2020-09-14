#pragma once

#include "Spark.h"
#include "SelectionManager.h"
#include "EditField/DefaultEditField.h"
#include "Spark/Engine/Level.h"

namespace Spark
{
    class DetailsPanel
    {
    public:
        void OnGUI()
        {
            ImGui::Begin("Details");
            Actor* actor = SelectionManager::Get().GetCurrentSelection();
            if(actor)
            {
                for(auto& c : actor->m_Components)
                {
                    ImGui::Text(c->GetStaticType().name);
                }
            }
            if(actor != nullptr && actor->HasComponent<TransformComponent>())
            {
                TransformEditField(*actor->GetComponent<TransformComponent>()).OnGUI();
            }
            ImGui::End();
        }
    };

}