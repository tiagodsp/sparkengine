#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"
#include "Spark/Renderer/IGraphicsContext.h"

namespace Spark
{
class SPARKENGINE_API RenderCommand
{
    friend class Renderer;
private:
    static Ref<PlatformRendererAPI> s_RendererAPI;

public:
    inline static void Init()
    {
        s_RendererAPI->Init();
    }
    
    inline static void SetClearColor(const glm::vec4 color)
    {
        s_RendererAPI->SetClearColor(color);
    }
    inline static void Clear()
    {
        s_RendererAPI->Clear();
    }

    inline static void DrawIndexed(const Ref<IVertexArray> &vertexArray)
    {
        s_RendererAPI->DrawIndexed(vertexArray);
    }

    inline static void SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height)
    {
        s_RendererAPI->SetViewport(X, Y, Width, Height);
    }
    
    inline static void SetGraphicsContext(Ref<IGraphicsContext> graphicsContext)
    {
        s_RendererAPI->SetGraphicsContext(graphicsContext);
    }
    
    inline static Ref<IGraphicsContext> GetGraphicsContext()
    {
        return s_RendererAPI->GetGraphicsContext();
    }
    
    inline static void Commit()
    {
        s_RendererAPI->Commit();
    }
};

} // namespace Spark
