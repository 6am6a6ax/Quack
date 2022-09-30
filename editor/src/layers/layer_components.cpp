#include "quack-editor/layers/layer_components.h"

#include <quack/quack.h>

Quack::LayerComponents::LayerComponents(SceneEditor * scene) : Layer("Components"), _scene(scene) {

}

Quack::LayerComponents::~LayerComponents() {

}

void Quack::LayerComponents::OnAttach() {
}

void Quack::LayerComponents::OnDetach() {
}

void Quack::LayerComponents::OnUpdate() {
    ImGui::Begin("Components");
    auto & entity = _scene->GetActiveEntity();
    if (entity != Entity()) {
        if (entity.HasComponent<TagComponent>()) {
            auto & tag = entity.GetComponent<TagComponent>().Tag;

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
                tag = std::string(buffer);
            }
        }
        if (entity.HasComponent<TransformComponent>()) {
            ImGui::DragFloat3("Translation", glm::value_ptr(entity.GetComponent<TransformComponent>().Translation), .1f);
            ImGui::Separator();
            ImGui::DragFloat3("Rotation", glm::value_ptr(entity.GetComponent<TransformComponent>().Rotation), .1f);
            ImGui::Separator();
            ImGui::DragFloat3("Scale", glm::value_ptr(entity.GetComponent<TransformComponent>().Scale), .1f);
        }
        if (entity.HasComponent<SpriteRendererComponent>()) {
            ImGui::ColorEdit4("Color", glm::value_ptr(entity.GetComponent<SpriteRendererComponent>().Color));
        }
//        if (entity.HasComponent<CameraComponent>()) {
//            auto & component = entity.GetComponent<CameraComponent>();
//        }
    }

    if (ImGui::Button("Add component")) {
        ImGui::OpenPopup("Add components");
    }

    if (ImGui::BeginPopup("Add components")) {
        if (ImGui::MenuItem("SpriteRendererComponent")) {
            _scene->GetActiveEntity().AddComponent<SpriteRendererComponent>();
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void Quack::LayerComponents::OnEvent(Quack::Event &) {
}
