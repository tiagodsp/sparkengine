#include "sparkengine.PCH.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Spark
{
    
OpenGLVertexArray::OpenGLVertexArray(/* args */)
{
    glGenVertexArrays(1, &m_RendererID);
    glBindVertexArray(m_RendererID);
    glBindVertexArray(0);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch(type)
    {
    case ShaderDataType::Float:       return GL_FLOAT;
    case ShaderDataType::Float2:      return GL_FLOAT;
    case ShaderDataType::Float3:      return GL_FLOAT;
    case ShaderDataType::Float4:      return GL_FLOAT;
    case ShaderDataType::Mat3:        return GL_FLOAT;
    case ShaderDataType::Mat4:        return GL_FLOAT;
    case ShaderDataType::Int:         return GL_INT;
    case ShaderDataType::Int2:        return GL_INT;
    case ShaderDataType::Int3:        return GL_INT;
    case ShaderDataType::Int4:        return GL_INT;
    case ShaderDataType::Bool:        return GL_BOOL;    
    }

    CORE_ASSERT(false, "Unknown ShaderDataType!");
    return GL_NONE;
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer)
{
    CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
    
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();
    uint32 layoutElementIndex = 0;
    auto elements = vertexBuffer->GetLayout().GetElements();
    for(auto element : elements)
    {
        glEnableVertexAttribArray(layoutElementIndex);
        glVertexAttribPointer(
            layoutElementIndex++,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBaseType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            vertexBuffer->GetLayout().GetStride(),
            ((const void*) element.Offset)
        );
    }
    vertexBuffer->Unbind();
    glBindVertexArray(0);
    m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();
    glBindVertexArray(0);
    
    m_IndexBuffer = indexBuffer;
}


} // namespace Spark