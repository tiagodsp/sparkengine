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

    virtual void SetClearColor(const glm::vec4 color) override;
    virtual void Clear() override;

    virtual void DrawIndexed(const std::shared_ptr<IVertexArray> &vertexArray) override;
};

} // namespace Spark