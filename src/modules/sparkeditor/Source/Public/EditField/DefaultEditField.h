#pragma once

#include "imgui.h"
#include "glm/glm.hpp"
#include "Spark/Engine/Object/Object.h"
#include "Spark/Engine/GameFramework/Actor.h"

namespace Spark
{
    class EditField
    {
    public:
        virtual void OnGUI() = 0;
    };

    class TransformEditField : public EditField
    {
        TransformComponent& m_TransformComponent;
    public:
        TransformEditField(TransformComponent& transformComponent) : m_TransformComponent(transformComponent) {}
        virtual void OnGUI() override
        {
            ImGui::InputFloat3("Position", (float*)&m_TransformComponent.Position, 3);
            ImGui::InputFloat3("Rotation", (float*)&m_TransformComponent.Rotation, 3);
            ImGui::InputFloat3("Scale", (float*)&m_TransformComponent.Scale, 3);
        }
    };
    
    // class TransformEditField : public EditField
    // {
    //     TransformComponent& m_TransformComponent;
    // public:
    //     TransformEditField(TransformComponent& transformComponent) : m_TransformComponent(transformComponent) {}
    //     virtual void OnGUI() override
    //     {
    //         ImGui::InputFloat3("Position", (float*)&m_TransformComponent.Position, 3);
    //         ImGui::InputFloat3("Rotation", (float*)&m_TransformComponent.Rotation, 3);
    //         ImGui::InputFloat3("Scale", (float*)&m_TransformComponent.Scale, 3);
    //     }
    // };
}