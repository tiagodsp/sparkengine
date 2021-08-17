#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Renderer/IVertexArray.h"
#include "Spark/Renderer/IGraphicsContext.h"
#include "glm/glm.hpp"

namespace Spark
{
    class SPARKENGINE_API PlatformRendererAPI
    {
    
    public:
        enum class API
        {
            None = 0,
            OpenGL = 1,
            Metal = 2,
        };

    public:
        virtual ~PlatformRendererAPI(){};
        
        virtual void Init() = 0;
        
        virtual void SetClearColor(const glm::vec4 color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const Ref<IVertexArray>& vertexArray) = 0;
        virtual void SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height) = 0;
        virtual void Commit() = 0;
        
        virtual void SetGraphicsContext(Ref<IGraphicsContext> graphicsContext) = 0;
        virtual Ref<IGraphicsContext> GetGraphicsContext() = 0;
    
        inline static API GetAPI() { return s_API; }
    
    protected:
        static API s_API;
    };
    
} // namespace Spark
