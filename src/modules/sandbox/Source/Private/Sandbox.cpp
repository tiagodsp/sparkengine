#include "Sandbox.h"
#include "LayerTest.h"
#include "LayerTest2D.h"

namespace Sandbox
{
    Sandbox::Sandbox()
    {
        this->PushLayer(new LayerTest2D());
        //this->PushLayer(new LayerTest());
    }

    Sandbox::~Sandbox()
    {

    }
}

Spark::Application* Spark::CreateApplication()
{
    return new Sandbox::Sandbox();
}