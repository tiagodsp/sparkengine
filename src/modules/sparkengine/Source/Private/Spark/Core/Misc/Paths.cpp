#include "Spark/CoreTypes.h"
#include <regex>
#include <sstream>
#include "Spark/Core/GenericPlatform/GenericPlatformFile.h"
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
        std::regex regex(R"([\\\/]*([\w\.]*\w)$)");
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
        std::regex regex(R"((.*?[\\\/]*?)(\w+)\.?\w*$)");
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
        std::regex regex(R"(^(.*?[\\\/]*?)([\w\.]*)\.?\w*$)");
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
        std::regex regex(R"(^(.*?[\\\/]*?)[\w\.]*\.?\w*$)");
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
        std::regex regex(R"(^(.*?[\\\/]*?)[\w\.]*\.?\w*$)");
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
        std::regex regex(R"(^.*?[\\\/]*?([\w\.]*)[\\\/]*?$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            return  matchs[1];
        }
        return "";
    }
    
    std::string Paths::GetPathLeaf(std::string& Path)
    {
        std::regex regex(R"(^.*?[\\\/]*?([\w\.]*)[\\\/]*?$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            return  matchs[1];
        }
        return "";
    }

    std::string Paths::ChangeExtensions(const std::string& Path, const std::string& NewExtension)
    {
        std::regex regex(R"(^(.*?[\\\/]*[\w\.]*?)\.?(\w*)$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        if(!matchs.empty())
        {
            std::ostringstream result;
            result << matchs[1] << "." << NewExtension;
            return  result.str();
        }
        return Path;
    }

    std::string Paths::SetExtension(const std::string& Path, const std::string& NewExtension)
    {
        std::regex regex(R"(^(.*?[\\\/]*[\w\.]*?)\.?(\w*)$)");
        std::smatch matchs;
        std::regex_match(Path, matchs, regex);
        std::ostringstream result;
        if(!matchs.empty())
        {
            result << matchs[1] << "." << NewExtension;
            return  result.str();
        }
        result << Path << "." << NewExtension;
        return result.str();
    }
    
    bool Paths::FileExists(const std::string& Path)
    {
        return IPlatformFile::Get()->Exists(Path);
    }
    
    bool Paths::DirectoryExists(const std::string& Path)
    {
        FileExists(Path);
    }
}