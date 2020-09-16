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
                    Type& t = c->GetDerivedType();
                    ImGui::TextColored({1,1,0,1}, t.name);
                    RenderGUIRecursive(t.name, (void*)c, &t);
                }
            }
            ImGui::End();
        }

        void RenderGUIRecursive(const char* varName, void* memberPtr, Type* type)
        {
            auto t = dynamic_cast<TypeClass*>(type);
            if(t != nullptr)
            {
                for(auto& m : t->members)
                {
                    RenderGUIRecursive(m.name, (void*)((char*)memberPtr + m.offset), m.type);   
                }
            }
            else
            {
                EditFieldFactory::Create(varName, (void*)memberPtr , type)->OnGUI();
            }
            
        }
    };

}