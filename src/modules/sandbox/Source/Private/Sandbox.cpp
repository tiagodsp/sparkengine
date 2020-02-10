#include "Sandbox.h"
#include <string>
#include "LayerTest.h"
#include "Spark/ImGui/ImGuiLayer.h"

namespace SandboxApp
{
    Sandbox::Sandbox()
    {
        this->PushLayer(new LayerTest());
        this->PushLayer(new Spark::ImGuiLayer());
    }

    Sandbox::~Sandbox()
    {

    }

    // void Sandbox::Run()
    // {
    //     Application::Run();
    // }
}
