#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Log
    {
        public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return Log::s_CoreLogger; };
        inline static std::shared_ptr<spdlog::logger>& GetUserLogger() { return Log::s_UserLogger; };

        private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_UserLogger;
    };
}

// Spark Core Logger macros
#define SC_LOG_TRACE(...)   ::Spark::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SC_LOG_INFO(...)    ::Spark::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SC_LOG_WARN(...)    ::Spark::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SC_LOG_ERROR(...)   ::Spark::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SC_LOG_FATAL(...)   ::Spark::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// User Logger macros
#define S_LOG_TRACE(...)   ::Spark::Log::GetUserLogger()->trace(__VA_ARGS__)
#define S_LOG_INFO(...)    ::Spark::Log::GetUserLogger()->info(__VA_ARGS__)
#define S_LOG_WARN(...)    ::Spark::Log::GetUserLogger()->warn(__VA_ARGS__)
#define S_LOG_ERROR(...)   ::Spark::Log::GetUserLogger()->error(__VA_ARGS__)
#define S_LOG_FATAL(...)   ::Spark::Log::GetUserLogger()->fatal(__VA_ARGS__)
