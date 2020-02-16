#pragma once

#include "sparkengine.api.gen.h"

class SPARKENGINE_API IGraphicsContext
{
public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
};
