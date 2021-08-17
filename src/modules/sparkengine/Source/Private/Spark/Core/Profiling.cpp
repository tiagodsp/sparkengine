#include "sparkengine.PCH.h"
#include "Spark/Core/Profiling.h"
#include "Spark/Core/Log.h"

static uint32 TotalAllocated = 0;
static uint32 TotalFreed = 0;


void* operator new(size_t size)
{
    if(TotalAllocated < size)
    {
        TotalAllocated = size;
    }
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    TotalFreed += size;
    free(memory);
}



namespace Spark
{
    Profiler& Profiler::Get()
    {
        static Profiler s_Instance;
        return s_Instance;
    }
    void Profiler::PushBack(const std::string& ScopeName, long long Duration)
    {
        m_ProfileScopeResults.insert_or_assign(ScopeName, Duration);
    }

} // namespace Spark
