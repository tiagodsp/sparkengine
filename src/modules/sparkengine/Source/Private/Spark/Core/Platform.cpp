#include "Spark/Core/Platform.h"
#include "Spark/CoreTypes.h"
#include "Platform/Windows/WindowsPlatform.h"

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
#if defined(_WIN32) || !defined(WIN32)
    return new WindowsPlatform();
#else
    CORE_ASSERT(false, "Unsupported platform!");
    return nullptr;
#endif
}

} // namespace Spark