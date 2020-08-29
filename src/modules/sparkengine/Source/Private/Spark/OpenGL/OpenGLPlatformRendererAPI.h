#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"

namespace Spark
{

class OpenGLPlatformRendererAPI : public PlatformRendererAPI
{
private:
    /* data */
public:
    OpenGLPlatformRendererAPI(/* args */);
    ~OpenGLPlatformRendererAPI();

    virtual void Init() override;
    virtual void SetClearColor(const glm::vec4 color) override;
    virtual void Clear() override;
    virtual void SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height) override;

    virtual void DrawIndexed(const Ref<IVertexArray> &vertexArray) override;
};

} // namespace Spark