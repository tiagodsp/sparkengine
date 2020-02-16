#include "sparkengine.PCH.h"
#include "WindowsPlatformWindow.h"

#include "Spark/Log.h"

#include "Spark/Events/ApplicationEvent.h"
#include "Spark/Events/KeyEvent.h"
#include "Spark/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLGraphicsContext.h"

#include "GLFW/glfw3.h"

namespace Spark
{
    static bool is_GLFWInitialized = false;

    // -----------------------------------------------------------------
    // PlatformWindow interface method implementation
    IPlatformWindow* IPlatformWindow::Create(const WindowProps& props)
    {
        return new WindowsPlatformWindow(props);
    }
    // ------------------------------------------------------------------

    WindowsPlatformWindow::WindowsPlatformWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsPlatformWindow::~WindowsPlatformWindow()
    {
        Shutdown();
    }

    void WindowsPlatformWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props. Width;
        m_Data.Height = props.Height;

        CORE_LOGI("Creating window {0} {1}, {2}", props.Title, props.Width, props.Height);


        if(!is_GLFWInitialized)
        {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();

            SC_ASSERT(success, "Could not initialize GLFW");
            glfwSetErrorCallback([](int error, const char* description){
                CORE_LOGF("GLFW Error ({0}): {1}", error, description);
            });
            is_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        
        m_GraphicsContext = new OpenGLGraphicsContext(m_Window);
        m_GraphicsContext->Init();
        
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

    void WindowsPlatformWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsPlatformWindow::OnUpdate()
    {
        glfwPollEvents();
        m_GraphicsContext->SwapBuffers();
    }

    void WindowsPlatformWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool WindowsPlatformWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}