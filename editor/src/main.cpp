#include <iostream>

#include "quack/application.h"

int main() {
    std::cout << "Hello, World! Starting...\n";

    Quack::ApplicationDescription appDesc;
    Quack::Application::GetInstance().SetDescription(std::forward<Quack::ApplicationDescription>(appDesc));

    Quack::WindowDescription windowDesc;
    windowDesc.SetSize({1280, 720});
    windowDesc.SetTitle("Quack Editor");
    Quack::Application::GetInstance().Init(std::forward<Quack::WindowDescription>(windowDesc));

    Quack::Application::GetInstance().Run();

    return 0;
}