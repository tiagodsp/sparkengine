#include "sparkengine.PCH.h"
#include "Spark/Engine/Mesh/MeshComponent.h"
#include <vector>
#include "Spark/Renderer/IBuffer.h"
#include "Spark/Engine/Mesh/MeshUtils.h"

namespace Spark
{
    MeshComponent::MeshComponent()
    {
        MarkAsDirty();
    }
    
    MeshComponent::MeshComponent(std::vector<MeshSectionData> MeshSections)
        : m_MeshSections(MeshSections)
    {
        MarkAsDirty();
    }

    MeshComponent::MeshComponent(std::string Filename)
    {
        MeshUtils::LoadMeshFromFile(m_MeshSections, Filename);
        MarkAsDirty();
    }
    
    MeshComponent::~MeshComponent()
    {

    }

    bool MeshComponent::CreateMeshSection(MeshSectionData MeshSection, int32 Index)
    {
        if(m_MeshSections.size() - 1 < Index)
        {
            m_MeshSections.resize(Index + 1);
        }
        m_MeshSections.insert(m_MeshSections.begin() + Index, MeshSection);
        return true;
    }
    
    bool MeshComponent::MarkAsDirty()
    {
        m_IsDirty = true;
        return m_IsDirty;
    }
    
    void MeshComponent::Update(Timestep ts)
    {
        if(m_IsDirty)
        {
            m_VertexArrays.empty();
            m_VertexArrays.reserve(m_MeshSections.size());

            for(int i = 0 ; i < m_MeshSections.size() ; i++)
            {
                Ref<IVertexBuffer> m_VertexBuffer;
                Ref<IIndexBuffer> m_IndexBuffer;

                std::vector<VertexData> sectionVerticesData;
                sectionVerticesData.reserve(m_MeshSections[i].Vertices.size());

                for(int j = 0 ; j < m_MeshSections[i].Vertices.size() ; j++)
                {
                    sectionVerticesData.emplace_back(
                        m_MeshSections[i].Vertices[j],
                        m_MeshSections[i].Normals[j],
                        m_MeshSections[i].UVs[j],
                        m_MeshSections[i].Colors[j]
                    );
                }
                
                float* v = reinterpret_cast<float*>(sectionVerticesData.data());

                m_VertexBuffer = Spark::IVertexBuffer::Create(v, sectionVerticesData.size() * sizeof(VertexData));
                m_VertexBuffer->SetLayout({
                    {Spark::ShaderDataType::Float3, "a_Position"},
                    {Spark::ShaderDataType::Float3, "a_Normal"},
                    {Spark::ShaderDataType::Float2, "a_TexCoord"},
                    {Spark::ShaderDataType::Float4, "a_Colors"}
                });

                m_IndexBuffer = Spark::IIndexBuffer::Create(m_MeshSections[i].Triangles.data(), m_MeshSections[i].Triangles.size());
                
                Ref<IVertexArray> va = IVertexArray::Create();
                va->AddVertexBuffer(m_VertexBuffer);
                va->SetIndexBuffer(m_IndexBuffer);
                m_VertexArrays.push_back(va);
            }
            m_IsDirty = false;
        }
    }

    std::vector<Ref<IVertexArray>>& MeshComponent::GetVertexArrays()
    {
        return m_VertexArrays;
    }

}

