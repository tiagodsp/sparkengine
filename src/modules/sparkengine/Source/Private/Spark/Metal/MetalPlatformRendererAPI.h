#pragma once

#include "Spark/Renderer/PlatformRendererAPI.h"
#include "MetalGraphicsContext.h"
#include <Metal/Metal.h>

namespace Spark
{
class MetalPlatformRendererAPI : public PlatformRendererAPI
{
    friend class MetalVertexBuffer;
    friend class MetalIndexBuffer;
    friend class MetalShader;
    friend class MetalFramebuffer;
    friend class MetalTexture2D;
    
private:
    Ref<MetalGraphicsContext> m_GraphicsContext;
    glm::vec4 m_ClearColor;
public:
    MetalPlatformRendererAPI(/* args */);
    ~MetalPlatformRendererAPI();
    
    virtual void Init() override;
    virtual void SetClearColor(const glm::vec4 color) override;
    virtual void Clear() override;
    virtual void SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height) override;
    virtual void Commit() override;
    
    virtual void SetGraphicsContext(Ref<IGraphicsContext> graphicsContext) override { m_GraphicsContext = std::static_pointer_cast<MetalGraphicsContext>(graphicsContext); }
    virtual Ref<IGraphicsContext> GetGraphicsContext() override { return m_GraphicsContext; };

    virtual void DrawIndexed(const Ref<IVertexArray> &vertexArray) override;
};

} // namespace Spark
