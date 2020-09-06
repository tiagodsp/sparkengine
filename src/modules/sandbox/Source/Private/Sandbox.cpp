#include "Sandbox.h"
#include "LayerTest.h"
#include "LayerTest2D.h"

namespace Sandbox
{
    Sandbox::Sandbox()
        : Application("Sandbox")
    {
        this->PushLayer(new LayerTest2D());
    }

    Sandbox::~Sandbox()
    {

    }
}

Spark::Application* Spark::CreateApplication()
{
    return new Sandbox::Sandbox();
}