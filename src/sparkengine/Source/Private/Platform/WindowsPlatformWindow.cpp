#include "sparkengine.PCH.h"

#include "Spark/Log.h"

#include "Platform/WindowsPlatformWindow.h"

namespace Spark
{
    static bool is_GLFWInitialized = false;

    IPlatformWindow* IPlatformWindow::Create(const WindowProps& props)
    {
        return new WindowsPlatformWindow(props);
    }

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

        SC_LOG_INFO("Creating window {0} {1}, {2}", props.Title, props.Width, props.Height);

        if(is_GLFWInitialized)
        {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();

            SC_ASSERT(success, "Could not initialize GLFW");

            is_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void WindowsPlatformWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsPlatformWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
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