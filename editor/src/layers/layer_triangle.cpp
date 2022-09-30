#include "quack-editor/layers/layer_triangle.h"

#include <quack/quack.h>

Quack::LayerTriangle::LayerTriangle(const std::string & name)
        : Layer(name),
          _camera(OrtographicCamera(-5.0f, 5.0f, -5.0f, 5.0f)) {}

Quack::LayerTriangle::~LayerTriangle() {

}

void Quack::LayerTriangle::OnAttach() {
    float vertices[3 * 9] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    };

    uint32_t indices[3] = { 0, 1, 2 };

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

            out vec4 o_Color;
            out vec2 o_TexCoord;

			void main()
			{
				gl_Position = u_ViewProj * vec4(a_Position, 1.0);
                o_Color = a_Color;
                o_TexCoord = a_TexCoord;
			}
		)";

    std::string fragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

            in vec4 o_Color;
            in vec2 o_TexCoord;

            uniform sampler2D u_Texture;

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
}

void Quack::LayerTriangle::OnDetach() {
    delete _framebuffer;
    delete _texture;
    delete _shader;
    delete _vao;
    delete _ebo;
    delete _vbo;
}
#include <iostream>

void Quack::LayerTriangle::OnUpdate() {
    static ImVec2 viewportSize = {1280, 720};
    static ImVec2 viewportSizePrev;
    if ((viewportSize.x != viewportSize.y) || (viewportSize.y != viewportSize.y)) {
        _framebuffer->Resize(viewportSize.x, viewportSize.y);
        viewportSizePrev = viewportSize;
    }

    _framebuffer->Bind();

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    _shader->Bind();
    _shader->UploadUniformMat4("u_ViewProj", _camera.GetViewProj());
    _shader->UploadUniformInt("u_Texture", 0);

    _vao->Bind();
    _texture->Bind();

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

    _framebuffer->Unbind();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGui::Begin("Triangle Test Viewport");

    viewportSize = ImGui::GetContentRegionAvail();

    uint32_t tex = _framebuffer->GetColorAttachment();
    ImGui::Image((void*)tex, ImVec2{viewportSize.x, viewportSize.y}, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::End();
    ImGui::PopStyleVar();
}

void Quack::LayerTriangle::OnEvent(Quack::Event &) {
}
