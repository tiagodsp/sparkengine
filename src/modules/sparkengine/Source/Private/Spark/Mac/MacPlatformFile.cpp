
#ifdef BUILD_MAC
#include "sparkengine.PCH.h"

#include "MacPlatformFile.h"

#include "Spark/Core/GenericPlatform/GenericPlatformFile.h"
#include <fstream>
#include <filesystem>

namespace Spark
{
    FileHandleMac::FileHandleMac(std::fstream& Handle)
        : m_Handle(Handle)
    {
    }

    FileHandleMac::~FileHandleMac()
    {
        m_Handle.close();
    }


    int64 FileHandleMac::Tell()
    {
        return m_Handle.tellg();
    }

    bool FileHandleMac::Seek(int64 NewPosition)
    {
        if(m_Handle.seekg(NewPosition, m_Handle.beg))
            return true;
        return false;
    }
    
    bool FileHandleMac::SeekFromEnd(int64 NewPositionRelativeToEnd)
    {
        if(m_Handle.seekg(NewPositionRelativeToEnd, m_Handle.end))
            return true;
        return false;
    }

    bool FileHandleMac::Read(uint8 *Destination, uint64 BytesToRead)
    {
        CORE_ASSERT(m_Handle.is_open(), "File handle is closed.");
        if(m_Handle.read(reinterpret_cast<char*>(Destination), BytesToRead))
            return true;
        return false;
    }

    bool FileHandleMac::Write(const uint8 *Source, int64 BytesToWrite)
    {
        CORE_ASSERT(m_Handle.is_open(), "File handle is closed.");
        if(m_Handle.write(reinterpret_cast<const char*>(Source), BytesToWrite))
            return true;
        return false;
    }
    
    bool FileHandleMac::Flush()
    {
        CORE_ASSERT(m_Handle.is_open(), "File handle is closed.");
        if(m_Handle.flush())
            return true;
        return false;
    }

    bool FileHandleMac::Truncate(int64 NewSize)
    {
        CORE_ASSERT(false, "FileHandleMac::Truncate not impelemented!");
        return false;
    }

    bool PlatformFileMac::FileExists(const char *Filename)
    {
        return std::filesystem::exists(Filename);
    }

    int64 PlatformFileMac::FileSize(const char *Filename)
    {
        return std::filesystem::file_size(Filename);
    }

    bool PlatformFileMac::DeleteFile(const char *Filename)
    {
        return std::filesystem::remove(Filename);
    }

    bool PlatformFileMac::IsReadOnly(const char *Filename)
    {
        std::filesystem::perms perm = std::filesystem::status(Filename).permissions();
        return (perm & std::filesystem::perms::owner_read) != std::filesystem::perms::none;
    }

    bool PlatformFileMac::MoveFile(const char* To, const char* From)
    {
        bool result = true;
        std::filesystem::perms p = std::filesystem::status(From).permissions();
        EPlatformFileRead r = (p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? EPlatformFileRead::AllowRead : EPlatformFileRead::None;
        EPlatformFileWrite w = (p & std::filesystem::perms::owner_read) != std::filesystem::perms::none ? EPlatformFileWrite::AllowWrite : EPlatformFileWrite::None;
        result &= CopyFile(To, From, r, w);
        result &= DeleteFile(From);
        return result;
    }

    bool PlatformFileMac::SetReadOnly(const char* Filename, bool NewReadOnlyValue)
    {
        CORE_ASSERT(false, "FileHandleMac::SetReadOnly not impelemented!");
        return false;
    }

    std::string PlatformFileMac::GetFilenameOnDisk(const char* Filename)
    {
        return std::filesystem::absolute(Filename).string();
    }

    IFileHandle* PlatformFileMac::OpenRead(const char* Filename, bool AllowWrite)
    {
        std::ios_base::openmode mode = std::ios::in | std::ios::binary;
        if(AllowWrite)
            mode |= std::ios::out;
        std::fstream* handle = new std::fstream(Filename, mode);
        if(*handle)
            return new FileHandleMac(*handle);
        return nullptr;
    }

    IFileHandle* PlatformFileMac::OpenWrite(const char* Filename, bool Append, bool AllowRead)
    {
        std::ios_base::openmode mode = std::ios::out| std::ios::binary;
        if(AllowRead)
            mode |= std::ios::in;
        std::fstream* handle = new std::fstream(Filename, mode);
        if(*handle)
            return new FileHandleMac(*handle);
        return nullptr;
    }

    bool PlatformFileMac::DirectoryExists(const char* Directory)
    {
        return std::filesystem::is_directory(Directory);
    }

    bool PlatformFileMac::CreateDirectory(const char* Directory)
    {
        return std::filesystem::create_directory(Directory);
    }

    bool PlatformFileMac::DeleteDirectory(const char* Directory)
    {
        return std::filesystem::remove(Directory);
    }

    void PlatformFileMac::FindFiles(std::vector<std::string>& FoundFiles, const char* Directory, const char* FileExtension)
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
    
    void PlatformFileMac::FindFilesRecursively(std::vector<std::string>& FoundFiles, const char* Directory, const char* FileExtension)
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
    
    bool PlatformFileMac::DeleteDirectoryRecursively(const char* Directory)
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
    
    bool PlatformFileMac::CreateDirectoryTree(const char* Directory)
    {
        return std::filesystem::create_directories(Directory);
    }

    bool PlatformFileMac::CopyFile(const char* To, const char* From, EPlatformFileRead ReadFlags, EPlatformFileWrite WriteFlags)
    {
        return std::filesystem::copy_file(From, To, std::filesystem::copy_options::update_existing);
    }

    bool PlatformFileMac::CopyDirectoryTree(const char* DestinationDirectory, const char* Source, bool OverwriteAllExisting)
    {
        CORE_ASSERT(false, "FileHandleMac::CopyDirectoryTree not impelemented!");
        return false;
    }

    // IPlatformFile Linux Implementation ------------------------
    IPlatformFile* IPlatformFile::Get()
    {
        static PlatformFileMac singleton;
        return &singleton;
    }
    // -------------------------------------------------------------
}

#endif //BUILD_MAC