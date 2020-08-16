#pragma once

#include "Spark/CoreTypes.h"
#include <string>
#include "sparkengine.api.gen.h"

namespace Spark
{
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

    class IPlatformFile
    {
    public:
        ~IPlatformFile(){}

        virtual bool FileExists(const char* filename) = 0;
        virtual int64 FileSize(const char* filename) = 0;
        virtual bool DeleteFile(const char* filename) = 0;
        virtual bool IsReadOnly(const char* filename) = 0;
        virtual bool MoveFile(const char* filename) = 0;
        virtual bool SetReadOnly(const char* filename, bool NewReadOnlyValue) = 0;
        virtual std::string GetFilenameOnDisk(const char* filename) = 0;

        virtual IFileHandle* OpenRead(const char* filename, bool AllowWrite = false) = 0;
        virtual IFileHandle* OpenWrite(const char* filename, bool Append = false, bool AllowRead = false) = 0;

        virtual bool DirectoryExists(const char* Directory) = 0;
        virtual bool CreateDirectory(const char* Directory) = 0;
        virtual bool DeleteDirectory(const char* Directory) = 0;
    };
}