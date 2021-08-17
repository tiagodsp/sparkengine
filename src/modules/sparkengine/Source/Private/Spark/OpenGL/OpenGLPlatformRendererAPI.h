#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"

namespace Spark
{

class OpenGLPlatformRendererAPI : public PlatformRendererAPI
{
private:
    Ref<IGraphicsContext> m_GraphicsContext;
public:
    OpenGLPlatformRendererAPI(/* args */);
    ~OpenGLPlatformRendererAPI();

    virtual void Init() override;
    virtual void SetClearColor(const glm::vec4 color) override;
    virtual void Clear() override;
    virtual void SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height) override;
    
    virtual void SetGraphicsContext(Ref<IGraphicsContext> graphicsContext) override { m_GraphicsContext = graphicsContext; }
    virtual Ref<IGraphicsContext> GetGraphicsContext() override { return m_GraphicsContext; };

    virtual void DrawIndexed(const Ref<IVertexArray> &vertexArray) override;
};

} // namespace Spark
