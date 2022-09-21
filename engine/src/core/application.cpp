#include "quack/core/application.h"

#include <GL/glew.h>

#include "quack/platform/glfw/window_glfw.h"

#include "quack/platform/imgui/layer_imgui.h"
#include "quack/graphics/gpu_buffer.h"
#include "quack/graphics/gpu_shader.h"
#include "quack/graphics/gpu_shader_program.h"
#include "quack/graphics/gpu_texture.h"

#include "quack/graphics/gpu_vertex_array.h"

#include "quack/render/ortographic_camera.h"

Quack::Application & Quack::Application::GetInstance() {
    static Application application;
    return application;
}

void Quack::Application::Init(const Quack::ApplicationDescription & desc) {
    SetDescription(desc);
    BindBaseCallbackAndLayerStack();
}

void Quack::Application::Run() {
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
    GPUBuffer * vertexBuffer = GetDevice()->CreateBuffer(vertexBufferDesc);

    GPUVertexArray * vertexArray = GetDevice()->CreateVertexArray();
    vertexArray->AddBuffer(*vertexBuffer);

    GPUBuffer::Description indexBufferDesc;
    indexBufferDesc.Data = &indices;
    indexBufferDesc.Size = sizeof(indices);
    indexBufferDesc.Type = BufferType::Index;
    GPUBuffer * indexBuffer = GetDevice()->CreateBuffer(indexBufferDesc);

    indexBuffer->Bind();
//
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
				color = texture(u_Texture, o_TexCoord);
			}
		)";

    GPUShaderProgramDescription vertexShaderProgramDesc;
    vertexShaderProgramDesc.Source = vertexShaderSrc;
    vertexShaderProgramDesc.Type = ShaderProgramType::Vertex;
    GPUShaderProgram * vertexShaderProgram = GetDevice()->CreateShaderProgram(vertexShaderProgramDesc);

    GPUShaderProgramDescription fragmentShaderProgramDesc;
    fragmentShaderProgramDesc.Source = fragmentShaderSrc;
    fragmentShaderProgramDesc.Type = ShaderProgramType::Fragment;
    GPUShaderProgram * fragmentShaderProgram = GetDevice()->CreateShaderProgram(fragmentShaderProgramDesc);

    GPUShaderDescription shaderDescription{};
    shaderDescription.VertexShader = vertexShaderProgram;
    shaderDescription.FragmentShader = fragmentShaderProgram;
    GPUShader * shader = GetDevice()->CreateShader(shaderDescription);

    GPUTextureDescription textureDescription;
    textureDescription.Path = "text.png";
    GPUTexture * texture = GetDevice()->CreateTexture(textureDescription);

//    GLuint m_VertexArray, m_VertexBuffer, m_IndexBuffer;
//
//    glGenVertexArrays(1, &m_VertexArray);
//    glBindVertexArray(m_VertexArray);
//
//    glGenBuffers(1, &m_VertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
//
//    float vertices[3 * 3] = {
//            -0.5f, -0.5f, 0.0f,
//            0.5f, -0.5f, 0.0f,
//            0.0f,  0.5f, 0.0f
//    };
//
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
//
//    uint32_t indices[3] = { 0, 1, 2 };
////    glGenBuffers(1, &m_IndexBuffer);
////    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
////    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    GPUBuffer::Description indexBufferDesc;
//    indexBufferDesc.Data = &indices;
//    indexBufferDesc.Size = sizeof(indices);
//    indexBufferDesc.Type = BufferType::Index;
//    GPUBuffer * indexBuffer = _description.GetDevice()->CreateBuffer(indexBufferDesc);
//
//    indexBuffer->Bind();

    OrtographicCamera camera(-1.0f, 1.0f, -1.0f, 1.0f);
    while (true) {
        //float time = (float)glfwGetTime(); //Application::GetTime();
        //Timestep timestep = time - _lastFrameTime;
        //static float _lastFrameTime = time;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //camera.SetRotation(camera.GetRotation() + .1f);
        //camera.SetPosition({0.5f, 0.5f, 0.0f});

        shader->Bind();
        shader->UploadUniformMat4("u_ViewProj", camera.GetViewProj());
        shader->UploadUniformInt("u_Texture", 0);

        vertexArray->Bind();

        texture->Bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        for (const auto & layer : GetLayerStack()) {
            layer->OnUpdate();
        }

        auto t = GetWindow();

        GetWindow()->OnUpdate();
    }
}

void Quack::Application::OnEvent(Quack::Event & e) {
    GetWindow()->OnEvent(e);
    for (const auto & layer : GetLayerStack()) {
        layer->OnEvent(e);
    }
}

const Quack::ApplicationDescription & Quack::Application::GetDescription() {
    return _desc;
}

void Quack::Application::BindBaseCallbackAndLayerStack() {
    GetWindow()->SetEventCallback(std::bind(&Quack::Application::OnEvent, this, std::placeholders::_1));
    GetLayerStack().Push(std::make_shared<LayerImGUI>());
}

void Quack::Application::SetDescription(const Quack::ApplicationDescription & desc) {
    _desc = desc;
}

Quack::Window * Quack::Application::GetWindow() {
    return _desc.Window;
}

void Quack::Application::SetWindow(Quack::Window * window) {
    _desc.Window = window;
}

Quack::GPUDevice * Quack::Application::GetDevice() {
    return _desc.GPUDevice;
}

void Quack::Application::SetDevice(Quack::GPUDevice * device) {
    _desc.GPUDevice = device;
}

Quack::LayerStack & Quack::Application::GetLayerStack() {
    return _desc.LayerStack;
}

void Quack::Application::SetLayerStack(const Quack::LayerStack & layerStack) {
    _desc.LayerStack = layerStack;
}

