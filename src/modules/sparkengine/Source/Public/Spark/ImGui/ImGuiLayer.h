#pragma once

#include "sparkengine.PCH.h"
#include "Spark/Core/Layer.h"
#include "imgui.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API ImGuiLayer : public Layer
    {
    public:
        virtual void Begin() = 0;
        virtual void End() = 0;
        virtual ImGuiContext* GetImGuiContext() = 0;
        static Ref<ImGuiLayer> Create();
    };
}
