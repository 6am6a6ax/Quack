#ifndef QUACK_LAYER_HIERARCHY_PANEL_H
#define QUACK_LAYER_HIERARCHY_PANEL_H

#include "quack/core/layer.h"
#include "quack-editor/scene_editor.h"

#include "quack/core/mouse_event.h"

namespace Quack {
class LayerHierarchyPanel final : public Layer {
public:
    LayerHierarchyPanel(const std::string & name, Quack::SceneEditor * scene);
    ~LayerHierarchyPanel() override;

public:
    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event &) override;

public:
    void OnMouseButtonPressed(MouseButtonPressedEvent &);

public:
    SceneEditor * GetScene() const;
    void SetScene(SceneEditor *);

public:
    SceneEditor * _scene;
};
}

#endif
