#pragma once
#include<sparkengine.api.gen.h>

namespace Spark
{
    class SPARKENGINE_API Application
    {
        public:
        Application();
        virtual ~Application();

        virtual void Run();
    };

    Application* CreateApplication();
    
}

