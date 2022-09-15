#ifndef QUACK_LAYER_IMGUI_H
#define QUACK_LAYER_IMGUI_H

#include "layer.h"

#include "key_event.h"
#include "mouse_event.h"
#include "window_event.h"

namespace Quack {
class LayerImGUI final : public Layer {
public:
    LayerImGUI();

public:
    void OnAttach() override;
    //void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event &&) override;

public:
    void OnWindowResizedEvent(WindowResizedEvent &&);

    void OnMouseMovedEvent(MouseMovedEvent &&);
    void OnMouseScrolledEvent(MouseScrolledEvent &&);
    void OnMouseButtonPressedEvent(MouseButtonPressedEvent &&);
    void OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &&);

    void OnKeyPressedEvent(KeyPressedEvent &&);
    void OnKeyReleasedEvent(KeyReleasedEvent &&);
};
}

#endif
