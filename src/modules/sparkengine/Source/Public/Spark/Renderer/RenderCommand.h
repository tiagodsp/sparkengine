#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"

namespace Spark
{
class SPARKENGINE_API RenderCommand
{
private:
    static PlatformRendererAPI *s_RendererAPI;

public:
    inline static void SetClearColor(const glm::vec4 color)
    {
        s_RendererAPI->SetClearColor(color);
    }
    inline static void Clear()
    {
        s_RendererAPI->Clear();
    }

    inline static void DrawIndexed(const std::shared_ptr<IVertexArray> &vertexArray)
    {
        s_RendererAPI->DrawIndexed(vertexArray);
    }
};

} // namespace Spark