#pragma once

#include "Spark/Core/GenericPlatform/GenericPlatformFile.h"
#include <fstream>

namespace Spark
{
    class FileHandleMac : public IFileHandle
    {
    public:
        
        FileHandleMac(std::fstream& Handle);
        virtual ~FileHandleMac();
        
        //IFileHandle overrides ------------------
        virtual int64 Tell() override;
        virtual bool Seek(int64 NewPosition) override;
        virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd) override;
        virtual bool Read(uint8 *Destination, uint64 BytesToRead) override;
        virtual bool Write(const uint8 *Source, int64 BytesToWrite) override;
        virtual bool Flush() override;
        virtual bool Truncate(int64 NewSize) override;

    private:
        std::fstream& m_Handle;
    };

    class PlatformFileMac : public IPlatformFile
    {
    public:
        
        //IPlatformFile overrides ---------------------------
        virtual bool FileExists(const char* Filename) override;
        virtual int64 FileSize(const char* Filename) override;
        virtual bool DeleteFile(const char* Filename) override;
        virtual bool IsReadOnly(const char* Filename) override;
        virtual bool MoveFile(const char* To, const char* From) override;
        virtual bool SetReadOnly(const char* Filename, bool NewReadOnlyValue) override;
        virtual std::string GetFilenameOnDisk(const char* Filename) override;

        virtual IFileHandle* OpenRead(const char* Filename, bool AllowWrite = false) override;
        virtual IFileHandle* OpenWrite(const char* Filename, bool Append = false, bool AllowRead = false) override;

        virtual bool DirectoryExists(const char* Directory) override;
        virtual bool CreateDirectory(const char* Directory) override;
        virtual bool DeleteDirectory(const char* Directory) override;

        virtual void FindFiles(std::vector<std::string>& FoundFiles, const char* Directory, const char* FileExtension) override;
        virtual void FindFilesRecursively(std::vector<std::string>& FoundFiles, const char* Directory, const char* FileExtension) override;
        virtual bool DeleteDirectoryRecursively(const char* Directory) override;
        virtual bool CreateDirectoryTree(const char* Directory) override;

        virtual bool CopyFile(const char* To, const char* From, EPlatformFileRead ReadFlags = EPlatformFileRead::None, EPlatformFileWrite WriteFlags = EPlatformFileWrite::None) override;
    	virtual bool CopyDirectoryTree(const char* DestinationDirectory, const char* Source, bool OverwriteAllExisting) override;
    };

} // namespace Spark
