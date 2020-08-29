#pragma once

#include <string>
#include <vector>
#include "Spark/Core/CoreTypes.h"
#include "sparkengine.api.gen.h"

namespace Spark
{

/**
 * General Shader datatypes definition.
 */ 
enum class ShaderDataType : uint8
{
    None = 0,
    Float, Float2, Float3,Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Bool
};

/**
 * Helper funtion to determine shader datatypes size.
 */ 
static uint32 ShaderDataTypeSize(ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::Float:       return 4;
        case ShaderDataType::Float2:      return 4 * 2;
        case ShaderDataType::Float3:      return 4 * 3;
        case ShaderDataType::Float4:      return 4 * 4;
        case ShaderDataType::Mat3:        return 4 * 3 * 3;
        case ShaderDataType::Mat4:        return 4 * 4 * 4;
        case ShaderDataType::Int:         return 4;
        case ShaderDataType::Int2:        return 4 * 2;
        case ShaderDataType::Int3:        return 4 * 3;
        case ShaderDataType::Int4:        return 4 * 4;
        case ShaderDataType::Bool:        return 1;    
        default:                          return 0;
    }

    CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

/**
 * BufferElement structure.
 */
struct BufferElement
{
    std::string Name;
    uint32 Offset;
    uint32 Size;
    ShaderDataType Type;
    bool Normalized;

    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
        : Type(type),
        Name(name),
        Normalized(normalized),
        Size(ShaderDataTypeSize(type)),
        Offset(0)
    {
    }

    uint32 GetComponentCount()
    {
        switch(Type)
        {
        case ShaderDataType::Float:       return 1;
        case ShaderDataType::Float2:      return 2;
        case ShaderDataType::Float3:      return 3;
        case ShaderDataType::Float4:      return 4;
        case ShaderDataType::Mat3:        return 3 * 3;
        case ShaderDataType::Mat4:        return 4 * 4;
        case ShaderDataType::Int:         return 1;
        case ShaderDataType::Int2:        return 2;
        case ShaderDataType::Int3:        return 3;
        case ShaderDataType::Int4:        return 4;
        case ShaderDataType::Bool:        return 1;    
        default:                          return 0;
        }

        CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }
};

/**
 * Defines a buffer layout using BufferElements.
 * Usage:
 * {    
 *      BufferLayout layout = 
 *      {
 *          {ShaderDataType::Float3, "a_Position"},
 *          {ShaderDataType::Float4, "a_Color"},
 *      };
 * }
 */
class SPARKENGINE_API BufferLayout
{
public:
    BufferLayout(const std::initializer_list<BufferElement>& elements)
        : m_Elements(elements)
        {
            CalculateOffsetAndStride();
        }
    inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    inline uint32 GetStride() const { return m_Stride; }
private:
    /**
     * Calculate Offset and Stride for whole layout.
     */
    void CalculateOffsetAndStride()
    {
        uint32 offset = 0;
        m_Stride = 0;
        for(auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }
private:
    std::vector<BufferElement> m_Elements;
    uint32 m_Stride = 0;
};


/**
 * Interface to define a VertexBuffer for plataform especific APIs.
 */
class SPARKENGINE_API IVertexBuffer
{
public:
    virtual ~IVertexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual BufferLayout GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout& layout) = 0;

    static Ref<IVertexBuffer> Create(float* vertices, uint32 size);
};

/**
 * Interface to define a IndexBuffer for plataform especific APIs.
 */
class SPARKENGINE_API IIndexBuffer
{
public:
    virtual ~IIndexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32 GetCount() const = 0;

    static Ref<IIndexBuffer> Create(uint32* indices, uint32 count);
};

} // namespace Spark
