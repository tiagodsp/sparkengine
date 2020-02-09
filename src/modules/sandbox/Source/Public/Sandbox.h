#include "Spark.h"
#include <iostream>
#include "Spark/Application.h"
#include "Spark/Events/ApplicationEvent.h"
//#include "sandbox.api.gen.h"

namespace SandboxApp
{
    class Sandbox : public Spark::Application
    {
        public:
        Sandbox();
        ~Sandbox();

        //void Run() override;
    };
}

Spark::Application* Spark::CreateApplication()
{
    return new SandboxApp::Sandbox();
}