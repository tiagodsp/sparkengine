#pragma once

#include "Spark/Renderer/IGraphicsContext.h"

struct GLFWwindow;

class OpenGLGraphicsContext : public IGraphicsContext
{
public:
    OpenGLGraphicsContext(GLFWwindow* windowHandle);

    virtual void Init() override;
    virtual void SwapBuffers() override;
private:
    GLFWwindow* m_windowHandle;
};

