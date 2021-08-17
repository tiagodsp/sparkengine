#include "sparkengine.PCH.h"
#include "MetalVertexArray.h"

namespace Spark
{
    
MetalVertexArray::MetalVertexArray(/* args */)
    : m_CurrentVertexBufferOffset(0)
{
}

MetalVertexArray::~MetalVertexArray()
{
    for(auto vb : m_VertexBuffers)
    {
        vb->Unbind();
    }
    m_IndexBuffer->Unbind();
}

void MetalVertexArray::Bind() const
{
    for(auto vb : m_VertexBuffers)
    {
        vb->Bind();
    }
}

void MetalVertexArray::Unbind() const
{
    // Implement Unbind...
}

//GLenum ShaderDataTypeToMetalBaseType(ShaderDataType type)
//{
//    switch(type)
//    {
//    case ShaderDataType::Float:       return GL_FLOAT;
//    case ShaderDataType::Float2:      return GL_FLOAT;
//    case ShaderDataType::Float3:      return GL_FLOAT;
//    case ShaderDataType::Float4:      return GL_FLOAT;
//    case ShaderDataType::Mat3:        return GL_FLOAT;
//    case ShaderDataType::Mat4:        return GL_FLOAT;
//    case ShaderDataType::Int:         return GL_INT;
//    case ShaderDataType::Int2:        return GL_INT;
//    case ShaderDataType::Int3:        return GL_INT;
//    case ShaderDataType::Int4:        return GL_INT;
//    case ShaderDataType::Bool:        return GL_BOOL;
//    }
//
//    CORE_ASSERT(false, "Unknown ShaderDataType!");
//    return GL_NONE;
//}

void MetalVertexArray::AddVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer)
{
    CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
    vertexBuffer->SetOffset(m_CurrentVertexBufferOffset);
    m_CurrentVertexBufferOffset += vertexBuffer->GetSize();
    m_VertexBuffers.push_back(vertexBuffer);
}

void MetalVertexArray::SetIndexBuffer(const Ref<IIndexBuffer>& indexBuffer)
{
    m_IndexBuffer = indexBuffer;
}


} // namespace Spark
