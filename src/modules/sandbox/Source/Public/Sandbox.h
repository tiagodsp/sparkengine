#pragma once

#include "Spark.h"

//#include "sandbox.api.gen.h"

namespace Sandbox
{
    class Sandbox : public Spark::Application
    {
        public:
        Sandbox();
        ~Sandbox();

        //void Run() override;
    };
}

