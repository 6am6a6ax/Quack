#ifndef QUACK_ENTITY_H
#define QUACK_ENTITY_H

#include <entt/entt.hpp>
#include "quack/scene/scene.h"

namespace Quack {
class Entity {
public:
    Entity() = default;
    Entity(entt::entity handle, Scene * scene) : _handle(handle), _scene(scene) {}

public:
    template<typename T, typename ...Args>
    T & AddComponent(Args && ...args) const {
        if (!HasComponent<T>())
            return _scene->_registry.emplace<T>(_handle, std::forward<Args>(args)...);
    }

    template<typename T>
    T & GetComponent() const {
        if (HasComponent<T>())
            return _scene->_registry.get<T>(_handle);
    }

    template<typename T>
    bool HasComponent() const {
        return _scene->_registry.any_of<T>(_handle);
    }

    template<typename T>
    void RemoveComponent() {
        if (HasComponent<T>())
            return _scene->_registry.remove<T>(_handle);
    }

public:
    operator entt::entity() const { return _handle; }

public:
    friend bool operator==(const Entity & lhs, const Entity & rhs) {
        if (lhs._handle == rhs._handle) {
            return true;
        }
        return false;
    }

    friend bool operator!=(const Entity & lhs, const Entity & rhs) {
        // TODO: Wrong statement
        if ((lhs._handle != rhs._handle) && (lhs._scene != rhs._scene)) {
            return true;
        }
        return false;
    }

public:
    entt::entity GetHandle() const { return _handle; }
    void SetHandle(entt::entity handle) { _handle = handle; }

    Scene * GetScene() const { return _scene; }
    void SetScene(Scene * scene) { _scene = scene; }

private:
    entt::entity _handle;
    Scene * _scene;
};
}

#endif