// #include "Sandbox.h"
// #include <string>

// namespace SandboxApp
// {
//     Sandbox::Sandbox()
//     {

//     }

//     Sandbox::~Sandbox()
//     {

//     }

//     // void Sandbox::Run()
//     // {
//     //     Application::Run();
//     // }
// }
#include <iostream>
#include <MyLib.h>
int main()
{
    std::cout << "TEST" << std::endl;
    MyLib::MyLibClass::saysomething();
    return 0;
}