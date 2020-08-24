#pragma once

#include "Spark/CoreTypes.h"
#include "Spark/Engine/Components/Component.h"
#include "Spark/Renderer/IVertexArray.h"
#include "glm/glm.hpp"
#include "sparkengine.api.gen.h"

namespace Spark
{
    struct MeshData
    {
        std::vector<glm::vec3>  Vertices;
        std::vector<glm::vec3>  Normals;
        std::vector<uint32>      Triangles;
        std::vector<glm::vec2>  UVs;
        std::vector<glm::vec4>  Colors;

        MeshData()
            : Vertices(), Normals(), Triangles(), UVs(), Colors()
        {}

        MeshData(
            std::vector<glm::vec3> Vertices,
            std::vector<glm::vec3> Normals,
            std::vector<uint32> Triangles,
            std::vector<glm::vec2> UVs,
            std::vector<glm::vec4> Colors)
            : Vertices(Vertices), Normals(Normals), Triangles(Triangles), UVs(UVs), Colors(Colors)
        {}
    };

    struct VertexData
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 UV;
        glm::vec3 Color;

        VertexData(glm::vec3 Position, glm::vec3 Normal, glm::vec2 UV, glm::vec3 Color)
            : Position(Position), Normal(Normal), UV(UV), Color(Color)
        {}
    };
    
    class SPARKENGINE_API MeshComponent : public Component
    {
    private:
        bool m_IsDirty;
        std::vector<MeshData> m_MeshSections;
        std::vector<Ref<IVertexArray>> m_VertexArrays;
    public:
        MeshComponent();
        MeshComponent(std::vector<MeshData> MeshSections);
        ~MeshComponent();

        bool CreateMeshSection(MeshData MeshSection, int32 Index);
        bool MarkAsDirty();
        virtual void Update(Timestep td) override;
        std::vector<Ref<IVertexArray>>& GetVertexArrays();
    };
} // namespace Spark
