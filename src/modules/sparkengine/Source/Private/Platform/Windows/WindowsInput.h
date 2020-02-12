#pragma once

#include "Spark/Input.h"

namespace Spark
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImp(int button) override;
        virtual std::pair<float, float> GetMousePositionImp() override;
        virtual float GetMouseXImp() override;
        virtual float GetMouseYImp() override;
    };
} // namespace Spark
