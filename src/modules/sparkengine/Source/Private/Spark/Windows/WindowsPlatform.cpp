#ifdef BUILD_WINDOWS
#include "Spark/Windows/WindowsPlatform.h"
#include "glfw/glfw3.h"

namespace Spark
{

WindowsPlatform::WindowsPlatform()
{
}

WindowsPlatform::~WindowsPlatform()
{
}

Timestep WindowsPlatform::GetTime() const
{
    float time = glfwGetTime();
    return Timestep(time);
}

} // namespace Spark
#endif //BUILD_WINDOWS