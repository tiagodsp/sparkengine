#include "sparkengine.PCH.h"
#include "OpenGLGraphicsContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* windowHandle)
    : m_windowHandle(windowHandle)
{
    CORE_ASSERT(windowHandle, "Window Handle is null!");
}

void OpenGLGraphicsContext:: Init()
{
    glfwMakeContextCurrent(m_windowHandle);      
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    CORE_ASSERT(status, "Failed to initialize GLAD.");

    CORE_LOGI("OpenGL Info:");
    CORE_LOGI("    Vendor: {0}", glGetString(GL_VENDOR));
    CORE_LOGI("    Renderer: {0}", glGetString(GL_RENDERER));
    CORE_LOGI("    Version: {0}", glGetString(GL_VERSION));
}

void OpenGLGraphicsContext::SwapBuffers()
{
    glfwSwapBuffers(m_windowHandle);
}