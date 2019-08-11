#include "Spark.h"
#include <iostream>
#include "sandbox.api.gen.h"

namespace SandboxApp
{
    class SANDBOX_API Sandbox : public Spark::Application
    {
        public:
        Sandbox();
        ~Sandbox();
    };
}

Spark::Application* Spark::CreateApplication()
{
    return new SandboxApp::Sandbox();
}