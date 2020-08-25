#pragma once

#include "Spark/CoreTypes.h"
#include "Spark/Engine/Components/Component.h"
#include "Spark/Renderer/IVertexArray.h"
#include "glm/glm.hpp"
#include "sparkengine.api.gen.h"

namespace Spark
{
    struct MeshSectionData
    {
        std::vector<glm::vec3>  Vertices;
        std::vector<glm::vec3>  Normals;
        std::vector<uint32>      Triangles;
        std::vector<glm::vec2>  UVs;
        std::vector<glm::vec4>  Colors;
        glm::mat4               Transform;

        MeshSectionData()
            : Vertices(), Normals(), Triangles(), UVs(), Colors(), Transform(glm::mat4(1.0f))
        {}

        MeshSectionData(
            std::vector<glm::vec3> Vertices,
            std::vector<glm::vec3> Normals,
            std::vector<uint32> Triangles,
            std::vector<glm::vec2> UVs,
            std::vector<glm::vec4> Colors,
            glm::mat4 Transform
            )
            : Vertices(Vertices), Normals(Normals), Triangles(Triangles), UVs(UVs), Colors(Colors), Transform(Transform)
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
        std::vector<MeshSectionData> m_MeshSections;
        std::vector<Ref<IVertexArray>> m_VertexArrays;
    public:
        MeshComponent();
        MeshComponent(std::vector<MeshSectionData> MeshSections);
        MeshComponent(std::string Filename);
        ~MeshComponent();

        virtual void Begin() override {}
        virtual void Update(Timestep ts) override;
        virtual void OnEvent(Event& e) override {}
        
        bool CreateMeshSection(MeshSectionData MeshSection, int32 Index);
        bool MarkAsDirty();
        std::vector<Ref<IVertexArray>>& GetVertexArrays();
    };
} // namespace Spark
