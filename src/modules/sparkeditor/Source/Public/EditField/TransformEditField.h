#pragma once

#include "imgui.h"
#include "glm/glm.hpp"
#include "Spark/Engine/Object/Object.h"
#include "Spark/Engine/GameFramework/Actor.h"

namespace Spark
{
    struct TransformEditField
    {
        static void OnGUI(TransformComponent& transformComponent)
        {
            ImGui::DragFloat3("Position", (float*)&transformComponent.Position, 0.01f, 0.0f, 100.0f);
        }
    };
}