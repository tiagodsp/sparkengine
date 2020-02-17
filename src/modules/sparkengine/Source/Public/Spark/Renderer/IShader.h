#pragma once
#include "sparkengine.api.gen.h"

class IShader
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
};
