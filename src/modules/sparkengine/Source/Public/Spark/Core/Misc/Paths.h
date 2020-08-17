
#pragma once

#include <string>
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Paths
    {
    public:
        
        /** Gets the filname extension
         * @param Path File path to get its extension.
         * @param IncludeDot if true, includes the extension leading dot on the result.
         * @return the extension of the filename, or a empty string if the filename doesn't have an extension.
         */        
        static std::string GetExtension(const std::string& Path, bool IncludeDot = false);
        
        /** Returns the filename (with extension), minus any path information. */
        static std::string GetCleanFilename(const std::string& Path);

        /** Returns the filename (without extension), minus any path information. */
        static std::string GetBaseFilename(const std::string& Path, bool RemovePath = true);
        /** Returns the filename (without extension), minus any path information. */
        static std::string GetBaseFilename(std::string& Path, bool RemovePath = true);

        // Returns the path in front of the filename.
        static std::string GetPath(const std::string& Path);
        // Returns the path in front of the filename.
        static std::string GetPath(std::string& Path);

        // Return the leaf in the path.
        static std::string GetPathLeaf(const std::string& Path);
        // Return the leaf in the path.
        static std::string GetPathLeaf(std::string& Path);

        // Changes the extension of the given Filename (does nothing if the file has no extension).
        static std::string ChangeExtensions(const std::string& Path, const std::string& NewExtension);

        // Sets the extension of the given Filename (if the file has no extension, sets a the new also).
        static std::string SetExtension(const std::string& Path, const std::string& NewExtension);
        
        // Returns true if this file was found, false otherwise.
        static bool FileExists(const std::string& Path);

        // Returns true if this directory was found, false otherwise.
        static bool DirectoryExists(const std::string& Path);

    };
}
