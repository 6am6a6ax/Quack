#ifndef EDITOR_APPLICATION_H
#define EDITOR_APPLICATION_H

#include "quack/application.h"

namespace Editor {
class Application : public Quack::Application {
public:
    explicit Application(Quack::ApplicationDescription &&);
};
}

#endif