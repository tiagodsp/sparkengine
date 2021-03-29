#ifdef BUILD_LINUX

#include "Spark/Linux/LinuxPlatform.h"
#include "GLFW/glfw3.h"

namespace Spark
{

LinuxPlatform::LinuxPlatform()
{
}

LinuxPlatform::~LinuxPlatform()
{
}

Timestep LinuxPlatform::GetTime() const
{
    float time = glfwGetTime();
    return Timestep(time);
}

} // namespace Spark

#endif //BUILD_LINUX