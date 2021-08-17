#ifdef BUILD_MAC

#include "sparkengine.PCH.h"
#include "MacPlatformWindow.h"

#include "Spark/Core/Log.h"

#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Events/KeyEvent.h"
#include "Spark/Events/MouseEvent.h"

#include "Spark/Renderer/Renderer.h"
#include "Spark/OpenGL/OpenGLGraphicsContext.h"
#include "Spark/Metal/MetalGraphicsContext.h"

#include "GLFW/glfw3.h"

namespace Spark
{
    static bool is_GLFWInitialized = false;

    // -----------------------------------------------------------------
    // PlatformWindow interface method implementation
    IPlatformWindow* IPlatformWindow::Create(const WindowProps& props)
    {
        return new MacPlatformWindow(props);
    }
    // ------------------------------------------------------------------

    MacPlatformWindow::MacPlatformWindow(const WindowProps& props)
    {
        Init(props);
    }

    MacPlatformWindow::~MacPlatformWindow()
    {
        Shutdown();
    }

    void MacPlatformWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props. Width;
        m_Data.Height = props.Height;

        CORE_LOGI("Creating window {0} {1}, {2}", props.Title, props.Width, props.Height);


        if(!is_GLFWInitialized)
        {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
//            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            CORE_ASSERT(success, "Could not initialize GLFW");
            glfwSetErrorCallback([](int error, const char* description){
                CORE_LOGF("GLFW Error ({0}): {1}", error, description);
            });
            is_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        
        m_GraphicsContext = std::make_shared<MetalGraphicsContext>(m_Window);
        m_GraphicsContext->Init();
        Renderer::SetGraphicsContext(m_GraphicsContext);
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        //Set GLFW callbacks ---------
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window,int width,int height){
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));            
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));            
            
            switch (action)
            {
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mode)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));             

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));             

            MouseScrollEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));             

            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

    }

    void MacPlatformWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void MacPlatformWindow::OnUpdate()
    {
        glfwPollEvents();
        m_GraphicsContext->SwapBuffers();
    }

    void MacPlatformWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool MacPlatformWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}

#endif //BUILD_MAC
