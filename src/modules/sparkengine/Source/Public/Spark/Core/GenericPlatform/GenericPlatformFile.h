#pragma once

#include "Spark/Core/CoreTypes.h"
#include <string>
#include <vector>
#include "sparkengine.api.gen.h"

namespace Spark
{
    enum class EPlatformFileRead : uint8
    {
        None = 0x0,
        AllowRead = 0x01
    };
    ENUM_ENABLE_BITMASK_OPERATORS(EPlatformFileRead);

    enum class EPlatformFileWrite : uint8
    {
        None = 0x0,
        AllowWrite = 0x01
    };
    ENUM_ENABLE_BITMASK_OPERATORS(EPlatformFileWrite);

    class SPARKENGINE_API IFileHandle
    {
    public:
        ~IFileHandle(){}

        /** 
         * Return the current write or read position. 
         * @return	    Current write or read position.
        **/
        virtual int64 Tell() = 0;
        
        /** 
         * Set the current write or read position. 
         * @param NewPosition   New seek postion.
         * @return	            true if successfuly changed to the new write or read position.
        **/
        virtual bool Seek(int64 NewPosition) = 0;

        /** 
         * Set the current write or read position relative to the end of file. 
         * @param NewPositionRelativeToEnd  New seek position relative to the end of the file.
         * @return	                        true is successfully changed to the new write or read position.
        **/
        virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd) = 0;

        /** 
         * Read bytes from the file. 
         * @param Destination   Buffer to holds the result, should be at least BytesToRead in size.
         * @param BytesToRead   Number of bytes to read into the destination.
         * @return	            true if the operation completed successfully.
        **/
        virtual bool Read(uint8* Destination, uint64 BytesToRead) = 0;

        /** 
         * Write bytes to the file. 
         * @param Source        Buffer to writen, should be at least BytesToWrite in size.
         * @param BytesToRead   Number of bytes to read into the destination.
         * @return	            true if the operation completed successfully.
        **/
        virtual bool Write(const uint8* Source, int64 BytesToWrite) = 0;

        /** 
         * Flushes the file handle to disk. 
         * @return  true if the operation completed successfully.
        **/
        virtual bool Flush() = 0;

        /** 
         * Truncate the file to given size (in bytes). 
         * @return  true if the operation completed successfully.
        **/
        virtual bool Truncate(int64 NewSize) = 0;

    };

    class SPARKENGINE_API IPlatformFile
    {
    public:
        
        static IPlatformFile* Get();
        
        ~IPlatformFile(){}

        virtual bool FileExists(const char* Filename) = 0;
        virtual int64 FileSize(const char* Filename) = 0;
        virtual bool DeleteFile(const char* Filename) = 0;
        virtual bool IsReadOnly(const char* Filename) = 0;
        virtual bool MoveFile(const char* To, const char* From) = 0;
        virtual bool SetReadOnly(const char* Filename, bool NewReadOnlyValue) = 0;
        virtual std::string GetFilenameOnDisk(const char* Filename) = 0;

        virtual IFileHandle* OpenRead(const char* Filename, bool AllowWrite = false) = 0;
        virtual IFileHandle* OpenWrite(const char* Filename, bool Append = false, bool AllowRead = false) = 0;

        virtual bool DirectoryExists(const char* Directory) = 0;
        virtual bool CreateDirectory(const char* Directory) = 0;
        virtual bool DeleteDirectory(const char* Directory) = 0;

        virtual void FindFiles(std::vector<std::string>& FoundFiles, const char* Directory, const char* FileExtension) = 0;
        virtual void FindFilesRecursively(std::vector<std::string>& FoundFiles, const char* Directory, const char* FileExtension) = 0;
        virtual bool DeleteDirectoryRecursively(const char* Directory) = 0;
        virtual bool CreateDirectoryTree(const char* Directory) = 0;

        virtual bool CopyFile(const char* To, const char* From, EPlatformFileRead ReadFlags = EPlatformFileRead::None, EPlatformFileWrite WriteFlags = EPlatformFileWrite::None) = 0;
    	virtual bool CopyDirectoryTree(const char* DestinationDirectory, const char* Source, bool OverwriteAllExisting) = 0;

    };
}