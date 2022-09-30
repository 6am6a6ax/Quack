#ifndef QUACK_SCENE_EDITOR_H
#define QUACK_SCENE_EDITOR_H

#include "quack/render/scene.h"
#include "quack/render/entity.h"

namespace Quack {
class SceneEditor final : public Scene {
public:
    SceneEditor() : Scene(), _activeEntity(Entity()) {}

public:
    const Entity & GetActiveEntity() const { return _activeEntity; }
    void SetActiveEntity(const Entity & entity) { _activeEntity = entity; }

private:
    Entity _activeEntity;
};
}

#endif
