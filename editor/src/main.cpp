#include <iostream>

#include "quack/application.h"

int main() {
    std::cout << "Hello, World! Starting...\n";

    Quack::ApplicationDescription appDesc;
    Quack::Application::GetInstance().SetDescription(appDesc);

    Quack::WindowDescription windowDesc;
    windowDesc.SetSize({1280, 720});
    windowDesc.SetTitle("Quack Editor");
    Quack::Application::GetInstance().Init(windowDesc);

    Quack::Application::GetInstance().Run();

    return 0;
}