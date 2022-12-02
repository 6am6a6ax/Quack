#include "quack-editor/layers/layer_hierarchy_panel.h"

#include <quack/quack.h>

Quack::Editor::LayerHierarchyPanel::LayerHierarchyPanel(const std::string & name, std::shared_ptr<Quack::SceneEditor> scene)
        : Layer(name),
          _scene(scene) {} // dynamic_cast = nullptr?!

Quack::Editor::LayerHierarchyPanel::~LayerHierarchyPanel() {

}

void Quack::Editor::LayerHierarchyPanel::OnAttach() {
    Layer::OnAttach();
}

void Quack::Editor::LayerHierarchyPanel::OnDetach() {
    Layer::OnDetach();
}

void Quack::Editor::LayerHierarchyPanel::OnUpdate() {
    ImGui::Begin("Scene Hierarchy");

    if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::MenuItem("Create an empty entity")) {
            _scene->CreateEntity("Empty");
        }
        ImGui::EndPopup();
    }

    _scene->GetRegistry().each([&](auto id) {
        auto entity = Entity(id, (Scene*)_scene);
        ImGuiTreeNodeFlags flags = ((_scene->GetActiveEntity() == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool isOpened = ImGui::TreeNodeEx((void *)(uint64_t)id, flags, GetScene()->GetRegistry().get<TagComponent>(id).Tag.c_str());
        if (ImGui::IsItemClicked()) {
            GetScene()->SetActiveEntity(entity);
        }

        if (isOpened) {
            ImGui::TreePop();
        }

        bool isDeleted = false;
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Remove entity")) {
                isDeleted = true;
            }
            ImGui::EndPopup();
        }

        if (isDeleted) {
            _scene->DestroyEntity(entity);
            if (_scene->GetActiveEntity() == entity) {
                _scene->SetActiveEntity({});
            }
        }
    });

    ImGui::End();
}

void Quack::Editor::LayerHierarchyPanel::OnEvent(Quack::Event & e) {
    switch (e.GetType()) {
        case EventType::MouseButtonPressedEvent:
            OnMouseButtonPressed(dynamic_cast<Quack::MouseButtonPressedEvent &>(e));
            break;
    }
}

std::shared_ptr<Quack::Editor::SceneEditor> Quack::Editor::LayerHierarchyPanel::GetScene() const {
    return _scene;
}

void Quack::Editor::LayerHierarchyPanel::SetScene(std::shared_ptr<Quack::Editor::SceneEditor> scene) {
    _scene = scene;
}

void Quack::Editor::LayerHierarchyPanel::OnMouseButtonPressed(Quack::MouseButtonPressedEvent & e) {
//    if (e.GetMouseCode() == Quack::MouseCode::ButtonRight && ImGui::BeginPopupContextWindow()) {
//        if (ImGui::MenuItem("Create an empty entity")) {
//            _scene->CreateEntity("Empty");
//        }
    //}
}
