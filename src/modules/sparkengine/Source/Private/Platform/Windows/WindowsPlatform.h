#pragma once
#include "Spark/Core/Platform.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

class WindowsPlatform : public Platform
{
private:
public:
    WindowsPlatform();
    virtual ~WindowsPlatform();

    virtual Timestep GetTime() const override;

};

} // namespace Spark