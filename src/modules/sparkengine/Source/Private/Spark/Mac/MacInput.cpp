#ifdef BUILD_MAC

#include "sparkengine.PCH.h"
#include "MacInput.h"

#include "Spark/Core/Application.h"

#include <GLFW/glfw3.h>
namespace Spark
{

    Input* Input::s_Instance = new MacInput();

    bool MacInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state  = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool MacInput::IsMouseButtonPressedImp(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state  = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> MacInput::GetMousePositionImp()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }

    float MacInput::GetMouseXImp()
    {
        auto[x,y] = GetMousePositionImp();
        return x;
    }

    float MacInput::GetMouseYImp()
    {
        auto[x,y] = GetMousePositionImp();
        return y;
    }

}

#endif //BUILD_MAC