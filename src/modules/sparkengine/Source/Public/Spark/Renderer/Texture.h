#pragma once

#include "Spark/Core/CoreTypes.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    
    class SPARKENGINE_API Texture
    {
    public:
        enum class PixelFormat : uint8
        {
            NONE,
            RGB, RGBA,
            BGR, BGRA,
            DXT, DXT5,
            ETC, ETC2,
            RED, GREEN, BLUE, APLHA
        };

        enum class TextureFormat : uint8
        {
            NONE,
            RGB8, RGBA8, RGB32, RGBA32,
            BGR8, BGRA8, BGR32, BGRA32,
            DXT, DXT5,
            ETC, ETC2
        };

        virtual uint32 GetWidth() const = 0;
        virtual uint32 GetHeight() const = 0;
        
        virtual void Bind(uint32 slot = 0) const = 0;
        virtual void Unbind() const = 0;
        virtual uint32 GetRendererID() const = 0;
        virtual void SetTextureData(const void* Data, size_t Size, PixelFormat PixelFormat) = 0;
    };

    class SPARKENGINE_API Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(uint32 Width, uint32 Height, TextureFormat TextureFormat);
        static Ref<Texture2D> Create(const std::string& filepath);
    };
}
