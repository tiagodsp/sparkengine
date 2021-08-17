#pragma once

#include "Spark/Renderer/IGraphicsContext.h"

#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.h>

struct GLFWwindow;

class MetalGraphicsContext : public IGraphicsContext
{
public:
    MetalGraphicsContext(GLFWwindow* windowHandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;
    
private:
    GLFWwindow* m_windowHandle;
public:
    id<MTLDevice> m_Device;
    CAMetalLayer* m_Layer;
    id<CAMetalDrawable> m_Surface;
};

