#include "sparkengine.api.gen.h"
#include "Spark/Engine/Mesh/MeshComponent.h"

namespace Spark
{
    class MeshUtils
    {
    public:
        static bool LoadMeshFromFile(std::vector<MeshSectionData>& MeshSections, std::string Filepath);
    };
} // namespace Spark
