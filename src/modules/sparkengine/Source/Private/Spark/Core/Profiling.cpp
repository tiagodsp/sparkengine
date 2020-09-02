#include "sparkengine.PCH.h"
#include "Spark/Core/Profiling.h"

namespace Spark
{
    Profiler& Profiler::Get()
    {
        static Profiler s_Instance;
        return s_Instance;
    }
    void Profiler::PushBack(const char *ScopeName, long long Duration)
    {
        m_ProfileScopeResults.insert_or_assign(ScopeName, Duration);
    }

} // namespace Spark