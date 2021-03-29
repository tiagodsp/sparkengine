#pragma once
#include "Spark/Core/Platform.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

class LinuxPlatform : public Platform
{
private:
public:
    LinuxPlatform();
    virtual ~LinuxPlatform();

    virtual Timestep GetTime() const override;

};

} // namespace Spark