#pragma once
#include "Spark/Core/Platform.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

class MacPlatform : public Platform
{
private:
public:
    MacPlatform();
    virtual ~MacPlatform();

    virtual Timestep GetTime() const override;

};

} // namespace Spark