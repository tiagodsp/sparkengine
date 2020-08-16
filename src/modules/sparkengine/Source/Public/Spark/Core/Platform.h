#pragma once
#include "Spark/Core/Timestep.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

class Platform
{
protected:
    static Platform *s_Instance;

public:
    static Platform *Get();

    // Interface methods ---------
    virtual Timestep GetTime() const = 0;

protected:
    Platform(){};
    virtual ~Platform(){}

private:
    static Platform *Create();
};

} // namespace Spark