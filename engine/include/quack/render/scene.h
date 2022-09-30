#ifndef QUACK_SCENE_H
#define QUACK_SCENE_H

#include <entt/entt.hpp>

namespace Quack {
class Entity;
class Scene {
    friend class Entity;

public:
    Scene();
    virtual ~Scene();

public:
    Entity CreateEntity(const std::string & name);
    void DestroyEntity(const Entity &);

public:
    void OnUpdate(float deltaTime) {}

public:
    const entt::registry & GetRegistry() const { return _registry; }

private:
    entt::registry _registry;
};
}

#endif
