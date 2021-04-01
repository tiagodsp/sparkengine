#include "Spark/Core/Platform.h"
#include "Spark/Core/CoreTypes.h"


#ifdef BUILD_WINDOWS
#include "Spark/Windows/WindowsPlatform.h"
#elif BUILD_LINUX
#include "Spark/Linux/LinuxPlatform.h"
#elif BUILD_MAC
#include "Spark/Mac/MacPlatform.h"
#endif


namespace Spark
{

Platform *Platform::s_Instance = nullptr;

Platform *Platform::Get()
{
    if (!s_Instance)
        s_Instance = Platform::Create();
    return s_Instance;
}

Platform *Platform::Create()
{
#ifdef BUILD_WINDOWS
    return new WindowsPlatform();
#elif BUILD_LINUX
    return new LinuxPlatform();
#elif BUILD_MAC
    return new MacPlatform();
#else
    CORE_ASSERT(false, "Unsupported platform!");
    return nullptr;
#endif
}

} // namespace Spark