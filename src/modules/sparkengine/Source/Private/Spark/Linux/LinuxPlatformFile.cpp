
#ifdef BUILD_LINUX
#include "sparkengine.PCH.h"

#include "LinuxPlatformFile.h"

#include "Spark/Core/GenericPlatform/GenericPlatformFile.h"
#include <fstream>
#include <filesystem>

namespace Spark
{
    FileHandleLinux::FileHandleLinux(std::fstream& Handle)
        : m_Handle(Handle)
    {
    }

    FileHandleLinux::~FileHandleLinux()
    {
        m_Handle.close();
    }


    int64 FileHandleLinux::Tell()
    {
        return m_Handle.tellg();
    }

    bool FileHandleLinux::Seek(int64 NewPosition)
    {
        if(m_Handle.seekg(NewPosition, m_Handle.beg))
            return true;
        return false;
    }
    
    bool FileHandleLinux::SeekFromEnd(int64 NewPositionRelativeToEnd)
    {
        if(m_Handle.seekg(NewPositionRelativeToEnd, m_Handle.end))
            return true;
        return false;
    }

    bool FileHandleLinux::Read(uint8 *Destination, uint64 BytesToRead)
    {
        CORE_ASSERT(m_Handle.is_open(), "File handle is closed.");
        if(m_Handle.read(reinterpret_cast<char*>(Destination), BytesToRead))
            return true;
        return false;
    }

    bool FileHandleLinux::Write(const uint8 *Source, int64 BytesToWrite)
    {
        CORE_ASSERT(m_Handle.is_open(), "File handle is closed.");
        if(m_Handle.write(reinterpret_cast<const char*>(Source), BytesToWrite))
            return true;
        return false;
    }
    
    bool FileHandleLinux::Flush()
    {
        CORE_ASSERT(m_Handle.is_open(), "File handle is closed.");
        if(m_Handle.flush())
            return true;
        return false;
    }

    bool FileHandleLinux::Truncate(int64 NewSize)
    {
        CORE_ASSERT(false, "FileHandleLinux::Truncate not impelemented!");
        return false;
    }

    bool PlatformFileLinux::FileExists(const char *Filename)
    {
        return std::filesystem::exists(Filename);
    }

    int64 PlatformFileLinux::FileSize(const char *Filename)
    {
        return std::filesystem::file_size(Filename);
    }

    bool PlatformFileLinux::DeleteFile(const char *Filename)
    {
        return std::filesystem::remove(Filename);
    }

    bool PlatformFileLinux::IsReadOnly(const char *Filename)
    {
        std::filesystem::perms perm = std::filesystem::status(Filename).permissions();
        return (perm & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
    }

    bool PlatformFileLinux::MoveFile(const char* To, const char* From)
    {
        bool result = true;
        std::filesystem::perms p = std::filesystem::status(From).permissions();
        EPlatformFileRead r = (p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? EPlatformFileRead::AllowRead : EPlatformFileRead::None;
        EPlatformFileWrite w = (p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? EPlatformFileWrite::AllowWrite : EPlatformFileWrite::None;
        result &= CopyFile(To, From, r, w);
        result &= DeleteFile(From);
        return result;
    }

    bool PlatformFileLinux::SetReadOnly(const char* Filename, bool NewReadOnlyValue)
    {
        CORE_ASSERT(false, "FileHandleLinux::SetReadOnly not impelemented!");
        return false;
    }

    std::string PlatformFileLinux::GetFilenameOnDisk(const char* Filename)
    {
        return std::filesystem::absolute(Filename).string();
    }

    IFileHandle* PlatformFileLinux::OpenRead(const char* Filename, bool AllowWrite)
    {
        std::ios_base::openmode mode = std::ios::in | std::ios::binary;
        if(AllowWrite)
            mode |= std::ios::out;
        std::fstream* handle = new std::fstream(Filename, mode);
        if(*handle)
            return new FileHandleLinux(*handle);
        return nullptr;
    }

    IFileHandle* PlatformFileLinux::OpenWrite(const char* Filename, bool Append, bool AllowRead)
    {
        std::ios_base::openmode mode = std::ios::out| std::ios::binary;
        if(AllowRead)
            mode |= std::ios::in;
        std::fstream* handle = new std::fstream(Filename, mode);
        if(*handle)
            return new FileHandleLinux(*handle);
        return nullptr;
    }

    bool PlatformFileLinux::DirectoryExists(const char* Directory)
    {
        return std::filesystem::is_directory(Directory);
    }

    bool PlatformFileLinux::CreateDirectory(const char* Directory)
    {
        return std::filesystem::create_directory(Directory);
    }

    bool PlatformFileLinux::DeleteDirectory(const char* Directory)
    {
        return std::filesystem::remove(Directory);
    }

    void PlatformFileLinux::FindFiles(std::vector<std::string>& FoundFiles, const char* Directory, const char* FileExtension)
    {
        for(auto entry : std::filesystem::directory_iterator(Directory))
        {
            if(!std::filesystem::is_directory(entry))
            {
                if(entry.path().extension() == FileExtension)
                {
                    FoundFiles.push_back(entry.path().string());
                }
            }
        }
    }
    
    void PlatformFileLinux::FindFilesRecursively(std::vector<std::string>& FoundFiles, const char* Directory, const char* FileExtension)
    {
        FindFiles(FoundFiles, Directory, FileExtension);
        for(auto entry : std::filesystem::directory_iterator(Directory))
        {
            if(std::filesystem::is_directory(entry))
            {
                FindFilesRecursively(FoundFiles, entry.path().string().c_str(), FileExtension);
            }
        }
    }
    
    bool PlatformFileLinux::DeleteDirectoryRecursively(const char* Directory)
    {
        bool result = true;
        for(auto entry : std::filesystem::directory_iterator(Directory))
        {
            if(std::filesystem::is_directory(entry))
            {
                result &= DeleteDirectoryRecursively(entry.path().string().c_str());
            }
        }
        result &= DeleteDirectory(Directory);
        return result;
    }
    
    bool PlatformFileLinux::CreateDirectoryTree(const char* Directory)
    {
        return std::filesystem::create_directories(Directory);
    }

    bool PlatformFileLinux::CopyFile(const char* To, const char* From, EPlatformFileRead ReadFlags, EPlatformFileWrite WriteFlags)
    {
        return std::filesystem::copy_file(From, To, std::filesystem::copy_options::update_existing);
    }

    bool PlatformFileLinux::CopyDirectoryTree(const char* DestinationDirectory, const char* Source, bool OverwriteAllExisting)
    {
        CORE_ASSERT(false, "FileHandleLinux::CopyDirectoryTree not impelemented!");
        return false;
    }

    // IPlatformFile Linux Implementation ------------------------
    IPlatformFile* IPlatformFile::Get()
    {
        static PlatformFileLinux singleton;
        return &singleton;
    }
    // -------------------------------------------------------------
}

#endif //BUILD_LINUX