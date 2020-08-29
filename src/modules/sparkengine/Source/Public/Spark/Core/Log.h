#pragma once

#include "Spark/Core/CoreTypes.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "map"
#include "string"

#include "sparkengine.api.gen.h"

namespace Spark
{
class SPARKENGINE_API Log
{
public:
    static void AddLogCategory(const std::string &logCategory);
    static void Init();
    inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return Log::GetLogger("Core"); };
    inline static std::shared_ptr<spdlog::logger> &GetLogger(const std::string &logCategory)
    {
        auto it = Log::s_LoggerMap.find(logCategory);
        CORE_ASSERT(it != Log::s_LoggerMap.end(), "Log category does not exist!");
        return it->second;
    };

private:
    static std::map<std::string, std::shared_ptr<spdlog::logger>> s_LoggerMap;
};
} // namespace Spark

// Spark Core Logger macros
#define CORE_LOGT(...) ::Spark::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOGI(...) ::Spark::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOGW(...) ::Spark::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOGE(...) ::Spark::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOGF(...) ::Spark::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Custom Logger macros
#define LOGT(LogCategory, ...) ::Spark::Log::GetLogger(#LogCategory)->trace(__VA_ARGS__)
#define LOGI(LogCategory, ...) ::Spark::Log::GetLogger(#LogCategory)->info(__VA_ARGS__)
#define LOGW(LogCategory, ...) ::Spark::Log::GetLogger(#LogCategory)->warn(__VA_ARGS__)
#define LOGE(LogCategory, ...) ::Spark::Log::GetLogger(#LogCategory)->error(__VA_ARGS__)
#define LOGF(LogCategory, ...) ::Spark::Log::GetLogger(#LogCategory)->critical(__VA_ARGS__)

#define DECLARE_LOG_CATEGORY(LogCategory)                                                        \
    struct _##LogCategory##LogCategoryDeclaration                                                \
    {                                                                                            \
        _##LogCategory##LogCategoryDeclaration() { ::Spark::Log::AddLogCategory(#LogCategory); } \
    } __##LogCategory##LogCategoryDeclaration;
