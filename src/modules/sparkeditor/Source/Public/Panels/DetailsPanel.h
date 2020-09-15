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
                    for(auto& m : c->GetDerivedType().members)
                    {
                        EditFieldFactory::Create((void*)((char*)c) + m->offset , m->type)->OnGUI();
                    }
                }
            }
            ImGui::End();
        }

        void RenderGUIRecursive(void* memberPtr, TypeClass* type)
        {
            for(auto m : type->members)
            {
                if((TypeClass*)m.type)
                {
                    RenderGUIRecursive((void*)(((char*)c) + m->offset), type);
                }
            }
        }
    };

}