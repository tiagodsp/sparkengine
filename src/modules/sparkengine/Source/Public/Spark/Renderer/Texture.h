#pragma once

#include "Spark/CoreTypes.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Texture
    {
    public:
        virtual uint32 GetWidth() const = 0;
        virtual uint32 GetHeight() const = 0;
        
        virtual void Bind() const = 0;
    };

    class SPARKENGINE_API Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& filepath);
    };
}
