#include "sparkengine.PCH.h"
#include "WindowsPlatformFile.h"

// namespace Spark
// {
//     std::vector<uint8> WindowsPlatformFile::ReadFileImp(const std::string& filepath)
//     {
//         std::string result;
//         std::ifstream in(filepath, std::ios::in | std::ios::binary);
//         if (in)
//         {
//             in.seekg(0, std::ios::end);
//             result.resize(in.tellg());
//             in.seekg(0, std::ios::beg);
//             in.read(&result[0], result.size());
//             in.close();
//         }
//         else
//         {
//             CORE_LOGE("Could not open file {0}", filepath);
//         }
//         return result;
//     }
// }


