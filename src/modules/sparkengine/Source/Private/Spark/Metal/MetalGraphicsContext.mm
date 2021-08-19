#include "sparkengine.PCH.h"
#include "MetalGraphicsContext.h"

#include <AppKit/AppKit.h>

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

MetalGraphicsContext::MetalGraphicsContext(GLFWwindow* windowHandle)
    : m_windowHandle(windowHandle)
    , m_Device(nil)
{
    CORE_ASSERT(windowHandle, "Window Handle is null!");
}

void MetalGraphicsContext:: Init()
{
    //glfwMakeContextCurrent(m_windowHandle);
    m_Device = MTLCreateSystemDefaultDevice();
    CORE_ASSERT(m_Device != nil, "Failed to initialize device.");
    
    // Create default layer
    m_Layer = [CAMetalLayer layer];
    m_Layer.device = m_Device;
    m_Layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    
    // Create window and set the default layer
    NSWindow *nswindow = glfwGetCocoaWindow(m_windowHandle);
    nswindow.contentView.layer = m_Layer;
    nswindow.contentView.wantsLayer = YES;
    
    // Create command queue
    m_CommandQueue = [m_Device newCommandQueue];
    
    // Create default render pass
    m_DefaultPass = [MTLRenderPassDescriptor renderPassDescriptor];
    m_DefaultPass.colorAttachments[0].clearColor = MTLClearColorMake(0, 0, 0, 1);
    m_DefaultPass.colorAttachments[0].loadAction = MTLLoadActionClear;
    m_DefaultPass.colorAttachments[0].storeAction = MTLStoreActionStore;
    m_DefaultPass.colorAttachments[0].texture = [m_Layer nextDrawable].texture;
    
//    // Create default command encoder to default pass
//    m_CommandBuffer = [m_CommandQueue commandBuffer];
//    m_CommandEncoder = [m_CommandBuffer renderCommandEncoderWithDescriptor:m_DefaultPass];
    
    // Log some information about the render
    CORE_LOGI("Metal Info:");
    CORE_LOGI("    Device: {0}", [[m_Device name]UTF8String]);
}

void MetalGraphicsContext::SwapBuffers()
{
    //m_Surface = [m_Layer nextDrawable];
}
