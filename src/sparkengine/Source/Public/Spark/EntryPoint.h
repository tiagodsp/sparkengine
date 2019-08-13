#pragma once

#ifndef __INTELLISENSE__
extern Spark::Application* Spark::CreateApplication();

int main(int argc, char const *argv[])
{
    Spark::Log::Init();
    SC_LOG_INFO("Initializing SparkEngine");
    
    Spark::Application* app = Spark::CreateApplication();
    app->Run();
    return 0;
}
#endif
