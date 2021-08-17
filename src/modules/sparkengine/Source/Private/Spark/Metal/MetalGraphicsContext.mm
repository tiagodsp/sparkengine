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
    
    m_Layer = [CAMetalLayer layer];
    m_Layer.device = m_Device;
    m_Layer.opaque = YES;
    
    NSWindow *nswindow = glfwGetCocoaWindow(m_windowHandle);
    nswindow.contentView.layer = m_Layer;
    nswindow.contentView.wantsLayer = YES;
    
    CORE_LOGI("Metal Info:");
    CORE_LOGI("    Device: {0}", [[m_Device name]UTF8String]);
}

void MetalGraphicsContext::SwapBuffers()
{
    //m_Surface = [m_Layer nextDrawable];
}
