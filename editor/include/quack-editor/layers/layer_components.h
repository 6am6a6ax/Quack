#ifndef QUACK_LAYER_COMPONENTS_H
#define QUACK_LAYER_COMPONENTS_H

#include "quack/core/layer.h"
#include "quack-editor/scene_editor.h"

namespace Quack::Editor {
class LayerComponents final : public Layer {
public:
    explicit LayerComponents(std::shared_ptr<SceneEditor> scene);
    ~LayerComponents() override;

public:
    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate() override;
    void OnEvent(Event &) override;

private:
    std::shared_ptr<SceneEditor> _scene;
};
}

#endif
