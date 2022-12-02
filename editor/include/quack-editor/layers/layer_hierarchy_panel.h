#ifndef QUACK_LAYER_HIERARCHY_PANEL_H
#define QUACK_LAYER_HIERARCHY_PANEL_H

#include "quack/core/layer.h"
#include "quack-editor/scene_editor.h"

#include "quack/core/mouse_event.h"

namespace Quack::Editor {
class LayerHierarchyPanel final : public Layer {
public:
    LayerHierarchyPanel(const std::string & name, std::shared_ptr<Quack::Editor::SceneEditor> scene);
    ~LayerHierarchyPanel() override;

public:
    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event &) override;

public:
    void OnMouseButtonPressed(MouseButtonPressedEvent &);

public:
    std::shared_ptr<SceneEditor> GetScene() const;
    void SetScene(std::shared_ptr<SceneEditor>);

public:
    std::shared_ptr<SceneEditor> _scene;
};
}

#endif
