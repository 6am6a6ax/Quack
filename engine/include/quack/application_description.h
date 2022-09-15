#ifndef QUACK_APPLICATION_DESCRIPTION_H
#define QUACK_APPLICATION_DESCRIPTION_H

#include <memory>

#include "window.h"
#include "layer_stack.h"

namespace Quack {
class ApplicationDescription {
public:
    ApplicationDescription();

    ApplicationDescription(const ApplicationDescription &) = default;
    ApplicationDescription(ApplicationDescription &&) = default;

    ApplicationDescription & operator=(const ApplicationDescription &) = default;
    ApplicationDescription & operator=(ApplicationDescription &&) = default;

    ~ApplicationDescription() = default;

public:
    Window * GetWindow();
    void SetWindow(std::shared_ptr<Window*> &&);

    LayerStack & GetLayerStack();
    void SetLayerStack(LayerStack &&);

private:
    std::shared_ptr<Window*> _window;
    LayerStack _layerStack;
};
}

#endif
