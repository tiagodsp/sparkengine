#include "Sandbox.h"
#include "LayerTest.h"

namespace Sandbox
{
    Sandbox::Sandbox()
    {
        this->PushLayer(new LayerTest());
    }

    Sandbox::~Sandbox()
    {

    }
}

Spark::Application* Spark::CreateApplication()
{
    return new Sandbox::Sandbox();
}