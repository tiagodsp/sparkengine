#pragma once

#include <map>
#include <chrono>
//#include <source_location>

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Profiler
    {
    private:
        std::map<std::string, long long> m_ProfileScopeResults;

    public:
        static Profiler &Get();
        void PushBack(const std::string& ScopeName, long long Duration);
        const std::map<std::string, long long>& GetResults() { return m_ProfileScopeResults; }
    };

    template <typename Fn>
    class Timer
    {
    private:
        std::string m_Name;
        Fn m_Callback;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;

    public:
        Timer(const std::string& name, Fn &&callback)
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


inline std::string methodName(const std::string& prettyFunction)
{
    size_t colons = prettyFunction.find("::");
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = prettyFunction.rfind("(") - begin;
    
    return prettyFunction.substr(begin,end).c_str();
}

#define __METHOD_NAME__ methodName(__PRETTY_FUNCTION__)

#define PROFILE_SCOPE(Name) Spark::Timer time##__LINE__(Name, [&](std::pair<std::string, long long> ProfileResult){ Spark::Profiler::Get().PushBack(ProfileResult.first, ProfileResult.second); })
#define PROFILE_FUNCTION() PROFILE_SCOPE(__METHOD_NAME__)