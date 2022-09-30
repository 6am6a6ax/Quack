#ifndef QUACK_LAYER_IMGUI_H
#define QUACK_LAYER_IMGUI_H

#include "quack/core/layer.h"

#include "quack/core/key_event.h"
#include "quack/core/mouse_event.h"
#include "quack/core/window_event.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

namespace Quack {
class LayerImGUI final : public Layer {
public:
    LayerImGUI();

public:
    void OnAttach() override;
    //void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event &) override;

public:
    void OnWindowResizedEvent(WindowResizedEvent &);

    void OnMouseMovedEvent(MouseMovedEvent &);
    void OnMouseScrolledEvent(MouseScrolledEvent &);
    void OnMouseButtonPressedEvent(MouseButtonPressedEvent &);
    void OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &);

    void OnKeyPressedEvent(KeyPressedEvent &);
    void OnKeyReleasedEvent(KeyReleasedEvent &);
};
}

#endif
