#pragma once

#include <map>
#include <chrono>

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Profiler
    {
    private:
        std::map<const char *, long long> m_ProfileScopeResults;

    public:
        static Profiler &Get();
        void PushBack(const char *ScopeName, long long Duration);
        const std::map<const char *, long long>& GetResults() { return m_ProfileScopeResults; }
    };

    template <typename Fn>
    class Timer
    {
    private:
        const char *m_Name;
        Fn m_Callback;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;

    public:
        Timer(const char *name, Fn &&callback)
            : m_Name(name), m_Callback(callback), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();
            long long duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimepoint - m_StartTimepoint).count();
            m_Callback({m_Name, duration});
            m_Stopped = true;
        }
    };
} // namespace Spark

#define PROFILE_SCOPE(Name) Spark::Timer time##__LINE__(Name, [&](std::pair<const char*, long long> ProfileResult){ Spark::Profiler::Get().PushBack(ProfileResult.first, ProfileResult.second); })