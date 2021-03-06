#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"

namespace Spark
{
class SPARKENGINE_API RenderCommand
{
private:
    static PlatformRendererAPI *s_RendererAPI;

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
};

} // namespace Spark