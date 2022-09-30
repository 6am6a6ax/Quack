#include "quack/quack.h"

Quack::Scene::Scene() {

}

Quack::Scene::~Scene() {

}

Quack::Entity Quack::Scene::CreateEntity(const std::string & name) {
    Entity entity = { _registry.create(), this };
    entity.AddComponent<TagComponent>(name);
    entity.AddComponent<TransformComponent>();
    return entity;
}

void Quack::Scene::DestroyEntity(const Quack::Entity & entity) {
    _registry.destroy(entity);
}

