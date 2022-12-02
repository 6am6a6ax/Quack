#ifndef QUACK_SCENE_SERIALIZER_H
#define QUACK_SCENE_SERIALIZER_H

#include "quack/render/scene.h"

namespace Quack {
class SceneSerializer {
public:
    explicit SceneSerializer(std::shared_ptr<Scene>);

public:
    void Serialize(std::shared_ptr<Scene> scene, const std::string & filepath);
    void SerializeRuntime(const std::string & filepath);

    void Deserialize(const std::string & filepath);
    void DeserializeRuntime(const std::string & filepath);

private:
    std::shared_ptr<Scene> _scene;
};
}

#endif
