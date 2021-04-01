#ifdef BUILD_MAC

#include "Spark/Mac/MacPlatform.h"
#include "GLFW/glfw3.h"

namespace Spark
{

MacPlatform::MacPlatform()
{
}

MacPlatform::~MacPlatform()
{
}

Timestep MacPlatform::GetTime() const
{
    float time = glfwGetTime();
    return Timestep(time);
}

} // namespace Spark

#endif //BUILD_MAC