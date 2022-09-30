#include "quack-editor/layers/layer_quad.h"
#include "quack-editor/scene_editor.h"

#include <quack/quack.h>

#include "ImGuizmo.h"

Quack::LayerQuad::LayerQuad(const std::string & name, Quack::SceneEditor * scene)
    : Layer(name),
    _scene(scene),
      _camera(OrtographicCamera(-10.0f, 10.0f, -10.0f, 10.0f)) {}

Quack::LayerQuad::~LayerQuad() {

}

void Quack::LayerQuad::OnAttach() {
    float vertices[4 * 9] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

    GPUBuffer::Layout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoord" }
    };

    GPUBuffer::Description vertexBufferDesc;
    vertexBufferDesc.LayoutDesc = layout;
    vertexBufferDesc.Data = &vertices;
    vertexBufferDesc.Size = sizeof(vertices);
    vertexBufferDesc.Type = BufferType::Vertex;
    _vbo = Quack::Application::GetInstance().GetDevice()->CreateBuffer(vertexBufferDesc);

    _vao = Quack::Application::GetInstance().GetDevice()->CreateVertexArray();
    _vao->AddBuffer(*_vbo);

    GPUBuffer::Description indexBufferDesc;
    indexBufferDesc.Data = &indices;
    indexBufferDesc.Size = sizeof(indices);
    indexBufferDesc.Type = BufferType::Index;
    _ebo = Quack::Application::GetInstance().GetDevice()->CreateBuffer(indexBufferDesc);
    _ebo->Bind();

    std::string vertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			layout(location = 2) in vec2 a_TexCoord;

            uniform mat4 u_ViewProj;
            uniform vec4 u_Color;
            uniform mat4 u_Transform;

            out vec4 o_Color;
            out vec2 o_TexCoord;

			void main()
			{
				gl_Position = u_Transform * u_ViewProj * vec4(a_Position, 1.0);
                o_Color = u_Color;
                o_TexCoord = a_TexCoord;
			}
		)";

    std::string fragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

            in vec4 o_Color;
            in vec2 o_TexCoord;


			void main()
			{
				color = o_Color;
			}
		)";

    GPUShaderProgramDescription vertexShaderProgramDesc;
    vertexShaderProgramDesc.Source = vertexShaderSrc;
    vertexShaderProgramDesc.Type = ShaderProgramType::Vertex;
    GPUShaderProgram * vertexShaderProgram = Quack::Application::GetInstance().GetDevice()->CreateShaderProgram(vertexShaderProgramDesc);

    GPUShaderProgramDescription fragmentShaderProgramDesc;
    fragmentShaderProgramDesc.Source = fragmentShaderSrc;
    fragmentShaderProgramDesc.Type = ShaderProgramType::Fragment;
    GPUShaderProgram * fragmentShaderProgram = Quack::Application::GetInstance().GetDevice()->CreateShaderProgram(fragmentShaderProgramDesc);

    GPUShaderDescription shaderDescription{};
    shaderDescription.VertexShader = vertexShaderProgram;
    shaderDescription.FragmentShader = fragmentShaderProgram;
    _shader = Quack::Application::GetInstance().GetDevice()->CreateShader(shaderDescription);

    GPUTextureDescription textureDescription;
    textureDescription.Path = "text.png";
    _texture = Quack::Application::GetInstance().GetDevice()->CreateTexture(textureDescription);

    GPUFramebufferDescription framebufferDescription;
    framebufferDescription.FrameSize = { 800, 600 };
    _framebuffer = Quack::Application::GetInstance().GetDevice()->CreateFramebuffer(framebufferDescription);

    Application::GetInstance().GetScene()->CreateEntity("Empty");

    _quad = Application::GetInstance().GetScene()->CreateEntity("Test Quad");
    _quad.AddComponent<SpriteRendererComponent>();

    _quad2 = Application::GetInstance().GetScene()->CreateEntity("Test Quad 2");
    _quad2.AddComponent<SpriteRendererComponent>();

    _scene->SetActiveEntity(_quad);
}

void Quack::LayerQuad::OnDetach() {
    delete _framebuffer;
    delete _texture;
    delete _shader;
    delete _vao;
    delete _ebo;
    delete _vbo;
}
#include <iostream>

void Quack::LayerQuad::OnUpdate() {
    static ImVec2 viewportSize = {1280, 720};
    static ImVec2 viewportSizePrev;

    if ((viewportSize.x != viewportSize.x) || (viewportSize.y != viewportSize.y)) {
        _framebuffer->Resize(viewportSize.x, viewportSize.y);
        viewportSizePrev = viewportSize;
    }

    _framebuffer->Bind();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    _shader->Bind();
    _shader->UploadUniformMat4("u_ViewProj", _camera.GetViewProj());
    _shader->UploadUniformVec4("u_Color", _quad.GetComponent<SpriteRendererComponent>().Color);
    _shader->UploadUniformMat4("u_Transform", _quad.GetComponent<TransformComponent>().GetTransform());

    _vao->Bind();
    _texture->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    _shader->Bind();
    _shader->UploadUniformMat4("u_ViewProj", _camera.GetViewProj());
    _shader->UploadUniformVec4("u_Color", _quad2.GetComponent<SpriteRendererComponent>().Color);
    _shader->UploadUniformMat4("u_Transform", _quad2.GetComponent<TransformComponent>().GetTransform());

    _vao->Bind();
    _texture->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    _framebuffer->Unbind();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Quad Test Viewport");

    viewportSize = ImGui::GetContentRegionAvail();

    uint32_t tex = _framebuffer->GetColorAttachment();
    ImGui::Image((void*)tex, ImVec2{viewportSize.x, viewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

    static auto _fakeCamera = TransformComponent();

    Entity selectedEntity = _scene->GetActiveEntity();
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

    const glm::mat4 & cameraProj = _camera.GetProjection();
    auto cameraView = glm::inverse(_fakeCamera.GetTransform());

    auto & selectedEntityTransformComponent = _scene->GetActiveEntity().GetComponent<TransformComponent>();
    glm::mat4 transform = selectedEntityTransformComponent.GetTransform();

    ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProj),
                         ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform));

    if (ImGuizmo::IsUsing()) {
    }


    ImGui::End();
    ImGui::PopStyleVar();
}

void Quack::LayerQuad::OnEvent(Quack::Event &) {
}
