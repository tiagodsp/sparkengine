#pragma once

#include <utility>
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Input
    {
    public:
        inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
        
        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImp(button); }
        inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImp(); }
        inline static float GetMouseX() { return s_Instance->GetMouseXImp(); }
        inline static float GetMouseY() { return s_Instance->GetMouseYImp(); }
        
    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImp(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImp() = 0;
        virtual float GetMouseXImp() = 0;
        virtual float GetMouseYImp() = 0;
        
        static Input* s_Instance;
    };
} // namespace Spark
