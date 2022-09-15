#include "quack-editor/application.h"

Editor::Application::Application(Quack::ApplicationDescription && desc)
    : Quack::Application(std::forward<Quack::ApplicationDescription>(desc))
{

}