#include "sparkengine.PCH.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Spark
{

// OpenGLVertexBuffer methods definitions ----------------
OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32 size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

BufferLayout OpenGLVertexBuffer::GetLayout() const
{

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

    SC_ASSERT(false, "Unknown ShaderDataType!");
    return GL_NONE;
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
{
    Bind();
    m_Layout = layout;
    uint32 layoutElementIndex = 0;
    for(BufferElement element : m_Layout.GetElements())
    {
        glEnableVertexAttribArray(layoutElementIndex);
        glVertexAttribPointer(
            layoutElementIndex++,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBaseType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            m_Layout.GetStride(),
            ((const void*) element.Offset)
        );
    }
    Unbind();

}

// -------------------------------------------------------

// OpenGLIndexBuffer methods definitions ----------------
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count)
{
    m_Count = count;
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace Spark