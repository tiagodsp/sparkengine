#include "sparkengine.PCH.h"

#include "Spark/Log.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Spark
{
    
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_UserLogger;

    void Log::Init()
    {
        std::cout << "Hue";
        //spdlog::sinks::sink
        spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
        s_CoreLogger = spdlog::stdout_color_mt("SPARK");
        s_CoreLogger->set_level(spdlog::level::trace);
        s_UserLogger = spdlog::stdout_color_mt("APP");
        s_UserLogger->set_level(spdlog::level::trace);
    }

}