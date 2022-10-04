//#include "quack/render/scene_serializer.h"
//
//#include <yaml-cpp/yaml.h>
//#include <fstream>
//
//#include "quack/render/entity.h"
//#include "quack/render/components.h"
//
//Quack::SceneSerializer::SceneSerializer(Quack::Scene * scene) : _scene(scene) {
//
//}
//
//static void SerializeEntity(YAML::Emitter & out, const Quack::Entity & entity) {
//    out << YAML::BeginMap;
//    out << YAML::Key << "Entity";
//    out << YAML::Value << (uint32_t)entity.GetHandle();
//
//    if (entity.HasComponent<Quack::TagComponent>()) {
//        out << YAML::Key << "TagComponent";
//        out << YAML::BeginMap;
//
//        auto & tag = entity.GetComponent<Quack::TagComponent>().Tag;
//        out << YAML::Key << "Tag" << YAML::Value << tag;
//        out << YAML::EndMap;
//    }
//
//    out << YAML::EndMap;
//}
//
//void Quack::SceneSerializer::Serialize(Quack::Scene * scene, const std::string & filepath) {
//    YAML::Emitter out;
//    out << YAML::BeginMap;
//    out << YAML::Key << "Scene";
//    out << YAML::Value << "Name";
//    out << YAML::Key << "Entities";
//    out << YAML::Value << YAML::BeginSeq;
//    scene->GetRegistry().each([&](auto id) {
//       Entity entity = { id, _scene };
////       if (!entity) {
////           return;
////       }
//       SerializeEntity(out, entity);
//    });
//
//    out << YAML::EndSeq;
//    out << YAML::EndMap;
//
//    std::ofstream fout(filepath);
//    fout << out.c_str();
//}
//
//void Quack::SceneSerializer::SerializeRuntime(const std::string & filepath) {
//
//}
//
//void Quack::SceneSerializer::Deserialize(const std::string & filepath) {
//
//}
//
//void Quack::SceneSerializer::DeserializeRuntime(const std::string & filepath) {
//
//}
