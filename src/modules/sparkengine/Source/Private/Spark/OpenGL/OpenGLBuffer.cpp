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
    m_Offset = 0;
    m_Size = size;
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
    return m_Layout;
}

void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
{
    m_Layout = layout;
}

// -------------------------------------------------------

// OpenGLIndexBuffer methods definitions ----------------
OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count)
{
    m_Count = count;
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
