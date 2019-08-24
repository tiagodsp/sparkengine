#include "Sandbox.h"

namespace SandboxApp
{
    Sandbox::Sandbox()
    {

    }

    Sandbox::~Sandbox()
    {

    }

    void Sandbox::Run()
    {
        Spark::WindowResizeEvent e(800, 600);
        S_LOG_INFO(e);
    }
}