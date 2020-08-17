#include "Spark/CoreTypes.h"
#include <regex>
#include <sstream>
#include <filesystem>
#include "Spark/Core/Misc/Paths.h"

namespace Spark
{
    std::string Paths::GetExtension(const std::string& Path, bool IncludeDot/* = false*/)
    {
        std::regex regex(R"(^.*\.([a-zA-Z0-9]+)$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            std::ostringstream result;
            result << (IncludeDot ? ".": "") << matchs[1];
            return  result.str();
        }
        return "";
    }
    
    std::string Paths::GetCleanFilename(const std::string& Path)
    {
        std::regex regex(R"([\\\/]*(\w+\.?\w*)$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            return  matchs[1];
        }
        return "";
    }

    std::string Paths::GetBaseFilename(const std::string& Path, bool RemovePath /*= true*/)
    {
        std::regex regex(R"((.+?[\\\/]*?)(\w+)\.?\w*$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            std::ostringstream result;
            result << ( RemovePath ? std::string("") : matchs[1] ) << matchs[2];
            return  result.str();
        }
        return "";
    }
    
    std::string Paths::GetBaseFilename(std::string& Path, bool RemovePath/* = true*/)
    {
        std::regex regex(R"((.+?[\\\/]*?)(\w+)\.?\w*$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            std::ostringstream result;
            result << ( RemovePath ? std::string("") : matchs[1] ) << matchs[2];
            return  result.str();
        }
        return "";
    }

    std::string Paths::GetPath(const std::string& Path)
    {
        std::regex regex(R"((.+?[\\\/]*?)\w+\.\w+$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            return  matchs[1];
        }
        return "";
    }
    
    std::string Paths::GetPath(std::string& Path)
    {
        std::regex regex(R"((.+?[\\\/]*?)\w+\.\w+$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            return  matchs[1];
        }
        return "";
    }

    std::string Paths::GetPathLeaf(const std::string& Path)
    {
        CORE_ASSERT(false, "Not implemented!");
        return std::string();
    }
    
    std::string Paths::GetPathLeaf(std::string& Path)
    {
        CORE_ASSERT(false, "Not implemented!");
        return std::string();
    }

    std::string Paths::ChangeExtensions(const std::string& Path, const std::string& NewExtension)
    {
        CORE_ASSERT(false, "Not implemented!");
        return std::string();
    }

    std::string Paths::SetExtension(const std::string& Path, const std::string& NewExtension)
    {
        CORE_ASSERT(false, "Not implemented!");
        return std::string();
    }
    
    bool Paths::FileExists(const std::string& Path)
    {
        CORE_ASSERT(false, "Not implemented!");
        return false;
    }
    
    bool Paths::DirectoryExists(const std::string& Path)
    {
        CORE_ASSERT(false, "Not implemented!");
        return false;
    }
}