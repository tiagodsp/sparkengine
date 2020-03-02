#include "sparkengine.PCH.h"

#include "Spark/Log.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"



namespace Spark
{
    std::map<std::string, std::shared_ptr<spdlog::logger>> Log::s_LoggerMap;

    void Log::Init()
    {
        spdlog::set_pattern("[%H:%M:%S %e] [%=10n] [%^%=10l%$] [thread %t] %v");
        DECLARE_LOG_CATEGORY(Core);
        DECLARE_LOG_CATEGORY(Temp);
    }

     void Log::AddLogCategory(const std::string& logCategory)
     {
        std::shared_ptr<spdlog::logger> logger = spdlog::stdout_color_mt(logCategory);
        logger->set_level(spdlog::level::trace);
        s_LoggerMap.insert(std::pair<std::string, std::shared_ptr<spdlog::logger>>(logCategory, logger));
     }
}