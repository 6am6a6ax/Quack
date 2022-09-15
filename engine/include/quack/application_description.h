#ifndef QUACK_APPLICATION_DESCRIPTION_H
#define QUACK_APPLICATION_DESCRIPTION_H

#include <memory>

#include "window.h"
#include "layer_stack.h"

namespace Quack {
class ApplicationDescription {
public:
    ApplicationDescription();

public:
    Window * GetWindow();
    void SetWindow(std::shared_ptr<Window*>);

    LayerStack & GetLayerStack();
    void SetLayerStack(const LayerStack &);

private:
    std::shared_ptr<Window*> _window;
    LayerStack _layerStack;
};
}

#endif
