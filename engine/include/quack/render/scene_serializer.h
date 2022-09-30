#ifndef QUACK_SCENE_SERIALIZER_H
#define QUACK_SCENE_SERIALIZER_H

#include "quack/render/scene.h"

namespace Quack {
class SceneSerializer {
public:
    explicit SceneSerializer(Scene * scene);

public:
    void Serialize(Scene * scene, const std::string & filepath);
    void SerializeRuntime(const std::string & filepath);

    void Deserialize(const std::string & filepath);
    void DeserializeRuntime(const std::string & filepath);

private:
    Scene * _scene;
};
}

#endif
