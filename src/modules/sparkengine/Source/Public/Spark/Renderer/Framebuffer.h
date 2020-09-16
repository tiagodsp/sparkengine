#pragma once

#include "Spark/Core/CoreTypes.h"
#include "glm/glm.hpp"
#include "sparkengine.api.gen.h"

namespace Spark
{
    struct FramebufferProperties
    {
        glm::vec2 Size;
        uint32 Samples = 1;
    };

    class SPARKENGINE_API IFramebuffer
    {
    public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Invalidate() = 0;
        virtual uint32 GetRendererID() = 0;
        virtual uint32 GetColorAttachmentRendererID() = 0;
        virtual uint32 GetDepthAttachmentRendererID() = 0;
        virtual const FramebufferProperties& GetProperties() const = 0;
        virtual void SetProperties(const FramebufferProperties& Properties) = 0;
        virtual void Resize(uint32 width, uint32 height) = 0;

        static Ref<IFramebuffer> Create(const FramebufferProperties& Properties);
    };

} // namespace Spark
