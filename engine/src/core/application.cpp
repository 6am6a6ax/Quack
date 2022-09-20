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

void Quack::Application::Init(const Quack::WindowDescription & windowDescription) {
    _description.SetWindow(std::make_shared<Quack::Window*>(Quack::WindowGLFW::Create(windowDescription)));

    // TODO
    //_description.GetWindow()->GetDescription().SetEventCallback(std::bind(&Quack::WindowGLFW::OnEvent, std::ref(*_description.GetWindow()), std::placeholders::_1));
    _description.GetWindow()->GetDescription().SetEventCallback(std::bind(&Quack::Application::OnEvent, this, std::placeholders::_1));

    _description.GetLayerStack().Push(std::make_shared<LayerImGUI>());
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
    GPUBuffer * vertexBuffer = _description.GetDevice()->CreateBuffer(vertexBufferDesc);

    GPUVertexArray * vertexArray = _description.GetDevice()->CreateVertexArray();
    vertexArray->AddBuffer(*vertexBuffer);

    GPUBuffer::Description indexBufferDesc;
    indexBufferDesc.Data = &indices;
    indexBufferDesc.Size = sizeof(indices);
    indexBufferDesc.Type = BufferType::Index;
    GPUBuffer * indexBuffer = _description.GetDevice()->CreateBuffer(indexBufferDesc);

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
    GPUShaderProgram * vertexShaderProgram = _description.GetDevice()->CreateShaderProgram(vertexShaderProgramDesc);

    GPUShaderProgramDescription fragmentShaderProgramDesc;
    fragmentShaderProgramDesc.Source = fragmentShaderSrc;
    fragmentShaderProgramDesc.Type = ShaderProgramType::Fragment;
    GPUShaderProgram * fragmentShaderProgram = _description.GetDevice()->CreateShaderProgram(fragmentShaderProgramDesc);

    GPUShaderDescription shaderDescription{};
    shaderDescription.VertexShader = vertexShaderProgram;
    shaderDescription.FragmentShader = fragmentShaderProgram;
    GPUShader * shader = _description.GetDevice()->CreateShader(shaderDescription);

    GPUTextureDescription textureDescription;
    textureDescription.Path = "text.png";
    GPUTexture * texture = _description.GetDevice()->CreateTexture(textureDescription);

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
        float time = (float)glfwGetTime(); //Application::GetTime();
        Timestep timestep = time - _lastFrameTime;
        _lastFrameTime = time;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //camera.SetRotation(camera.GetRotation() + .1f);
        //camera.SetPosition({0.5f, 0.5f, 0.0f});

        shader->Bind();
        shader->UploadUniformMat4("u_ViewProj", camera.GetViewProj());
        shader->UploadUniformInt("u_Texture", 0);

        vertexArray->Bind();

        texture->Bind();


//        shader->Bind();
//        glBindVertexArray(m_VertexArray);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        for (const auto & layer : _description.GetLayerStack()) {
            layer->OnUpdate();
        }
        _description.GetWindow()->OnUpdate();
    }
}

void Quack::Application::OnEvent(Quack::Event & e) {
    _description.GetWindow()->OnEvent(e);
    for (const auto & layer : _description.GetLayerStack()) {
        layer->OnEvent(e);
    }
}

Quack::ApplicationDescription & Quack::Application::GetDescription() {
    return _description;
}

void Quack::Application::SetDescription(Quack::ApplicationDescription & description) {
    _description = std::forward<Quack::ApplicationDescription>(description);
}

