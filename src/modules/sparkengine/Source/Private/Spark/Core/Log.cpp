#include "sparkengine.PCH.h"

#include "Spark/Core/Log.h"
#include "Spark/Core/CoreTypes.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"



namespace Spark
{
    std::map<std::string, Ref<spdlog::logger>> Log::s_LoggerMap;

    void Log::Init()
    {
        spdlog::set_pattern("[%H:%M:%S %e] [%=10n] [%^%=10l%$] [thread %t] %v");
        DECLARE_LOG_CATEGORY(Core);
        DECLARE_LOG_CATEGORY(Temp);
    }

     void Log::AddLogCategory(const std::string& logCategory)
     {
        Ref<spdlog::logger> logger = spdlog::stdout_color_mt(logCategory);
        logger->set_level(spdlog::level::trace);
        s_LoggerMap.insert(std::pair<std::string, Ref<spdlog::logger>>(logCategory, logger));
     }

    std::shared_ptr<spdlog::logger> &Log::GetLogger(const std::string &logCategory)
    {
        auto it = Log::s_LoggerMap.find(logCategory);
        CORE_ASSERT(it != Log::s_LoggerMap.end(), "Log category does not exist!");
        return it->second;
    }
}