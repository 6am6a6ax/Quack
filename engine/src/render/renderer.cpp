#include "quack/graphics/gpu_texture.h"
#include "quack/quack.h"
#include <memory>

void Quack::Renderer::Begin() {}
void Quack::Renderer::End() {}

void Quack::Renderer::RenderQuad() {
    float vertices[4 * 9] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };

    uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

    Quack::GPUBuffer::Layout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" },
        { ShaderDataType::Float2, "a_TexCoord" }
    };

    Quack::GPUBuffer::Description vboDesc;
    vboDesc.LayoutDesc = layout;
    vboDesc.Data = &vertices;
    vboDesc.Size = sizeof(vertices);
    vboDesc.Type = BufferType::Vertex;
    std::shared_ptr<Quack::GPUBuffer> vbo = Quack::Application::GetInstance().GetDevice()->CreateBuffer(vboDesc);

    std::shared_ptr<Quack::GPUVertexArray> vao = Quack::Application::GetInstance().GetDevice()->CreateVertexArray();
    vao->AddBuffer(vbo);

    Quack::GPUBuffer::Description iboDesc;
    iboDesc.Data = &indices;
    iboDesc.Size = sizeof(indices);
    iboDesc.Type = BufferType::Index;
    std::shared_ptr<Quack::GPUBuffer> ibo  = Quack::Application::GetInstance().GetDevice()->CreateBuffer(iboDesc);
    ibo->Bind();

    std::shared_ptr<Quack::GPUShader> shader = Quack::Application::GetInstance().GetAssetLibrary().LoadShader("basic.glsl");
    //shader->UploadUniformMat4f("u_ViewProj", Quack::Application::GetInstance().GetCamera()->GetViewProj());

    std::shared_ptr<Quack::GPUTexture> texture = Quack::Application::GetInstance().GetAssetLibrary().LoadTexture("western_red_cedar.jpg");

    vao->Bind();
    shader->Bind();
    texture->Bind();

    Quack::Application::GetInstance().GetDevice()->DrawIndexed(6);
}