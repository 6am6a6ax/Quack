#include "quack-editor/layers/layer_quad.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "quack-editor/scene_editor.h"

#include <memory>
#include <quack/quack.h>

#include "ImGuizmo.h"
#include "quack/core/application.h"
#include "quack/math/math.h"

Quack::Editor::LayerQuad::LayerQuad(const std::string & name)
    : Layer(name), _light(DirectionalLight(Mat4f(1.0f))) {}

Quack::Editor::LayerQuad::~LayerQuad() {}

void Quack::Editor::LayerQuad::OnAttach() {
    GPUFramebufferDescription framebufferDescription;
    framebufferDescription.FrameSize = { 1280, 720 };
    _framebuffer = Quack::Application::GetInstance().GetDevice()->CreateFramebuffer(framebufferDescription);

    _model = std::make_shared<Model>("/home/bujhm/dev/cpp/cg/quack/engine/assets/models/suzanne/suzanne.blend");
    //_model = std::make_shared<Model>("/home/bujhm/dev/cpp/cg/quack/engine/assets/models/building/building.fbx");

    _light = DirectionalLight(Mat4f(1.0f), { 2.0f, 2.0f, 2.0f }, {1.0f, 1.0f, 1.0f}, .5f);

    if (_model->GetIndices().size() > 0) {
        std::cout << "Model loaded!\n";
    }
    else {
        std::cout << "Error!\n";
    }
}

void Quack::Editor::LayerQuad::OnDetach() {
}

void Quack::Editor::LayerQuad::OnUpdate() {
    static ImVec2 viewportSize = {1280, 720};
    static ImVec2 viewportSizePrev;

    if ((viewportSize.x != viewportSize.x) || (viewportSize.y != viewportSize.y)) {
        _framebuffer->Resize(viewportSize.x, viewportSize.y);
        viewportSizePrev = viewportSize;
    }

    ImGui::Begin("Light control");
    ImGui::ColorEdit4("Color", glm::value_ptr(_light._color));
    ImGui::DragFloat("Intensity", &_light._intensity, .01f);
    ImGui::End();

    _framebuffer->Bind();

    Application::GetInstance().GetDevice()->Enable(Quack::GPUDevice::CommonFlag::DEPTH_TEST);
    Application::GetInstance().GetDevice()->Clear(Quack::GPUDevice::ClearFlag::COLOR_BUFFER);
    Application::GetInstance().GetDevice()->Clear(Quack::GPUDevice::ClearFlag::DEPTH_BUFFER);
    Application::GetInstance().GetDevice()->ClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Application::GetInstance().GetDevice()->SetDepthFunc(Quack::GPUDevice::DepthFuncFlag::LESS);

    //Application::GetInstance().GetAssetLibrary().LoadModel("building/building.obj");

    // glPolygonMode(GL_FRONT, GL_LINE);
    // glPolygonMode(GL_BACK, GL_LINE);

    glFrontFace(GL_CCW);

    Renderer::Begin();
    // Renderer::RenderModel(_model, _light, Mat4f(1.0f));
    //Renderer::RenderGrid();
    // Renderer::RenderQuad();
    // Renderer::RenderCube();
    Renderer::End();

    _framebuffer->Unbind();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Quad Test Viewport");

    viewportSize = ImGui::GetContentRegionAvail();

    uint32_t tex = _framebuffer->GetColorAttachment();
    ImGui::Image(reinterpret_cast<void*>(tex), ImVec2{viewportSize.x, viewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::End();
    ImGui::PopStyleVar();
}

void Quack::Editor::LayerQuad::OnEvent(Quack::Event &) {
}
