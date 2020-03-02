#pragma once

extern Spark::Application* Spark::CreateApplication();

int main(int argc, char const *argv[])
{
    Spark::Log::Init();
    DECLARE_LOG_CATEGORY(MyLog);
    CORE_LOGI("Initializing SparkEngine");

    Spark::Application *app = Spark::CreateApplication();
    app->Run();
    return 0;
}