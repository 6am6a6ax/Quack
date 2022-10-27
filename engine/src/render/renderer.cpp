#include "quack/platform/vulkan/gpu_pipeline_vulkan.h"
#include "quack/quack.h"
#include "quack/render/renderer.h"

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

    std::shared_ptr<Quack::GPUShader> shader = Quack::Application::GetInstance().GetAssetLibrary().LoadShader("quad_camera.glsl");

    std::shared_ptr<Quack::GPUTexture> texture = Quack::Application::GetInstance().GetAssetLibrary().LoadTexture("western_red_cedar.jpg");

    vao->Bind();
    shader->Bind();
    shader->UploadUniformMat4f("u_ViewProj", Quack::Application::GetInstance().GetCamera()->GetViewProj());
    texture->Bind();

    Quack::Application::GetInstance().GetDevice()->DrawIndexed(6);
}

void Quack::Renderer::RenderGrid() {
    float vertices[4 * 9] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

    Quack::GPUBuffer::Layout layout = {
        { ShaderDataType::Float3, "a_Position" },
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

    std::shared_ptr<Quack::GPUShader> shader = Quack::Application::GetInstance().GetAssetLibrary().LoadShader("grid.glsl");

    vao->Bind();
    shader->Bind();
    shader->UploadUniformMat4f("u_ViewProj", Quack::Application::GetInstance().GetCamera()->GetViewProj());

    Quack::Application::GetInstance().GetDevice()->DrawIndexed(6);
}

void Quack::Renderer::RenderCube() {
    float vertices[] = {
        -1.0, -1.0,  1.0, .70f , 0.32f , 0.31f ,
         1.0, -1.0,  1.0, .20f , 0.4f , 0.21f ,
         1.0,  1.0,  1.0, .50f , 0.32f , 0.71f ,
        -1.0,  1.0,  1.0, .60f , 0.62f , 0.11f ,
        // back
        -1.0, -1.0,  -1.0, .30f , 0.87f , 0.60f ,
         1.0, -1.0, -1.0, .30f , 0.87f , 0.f ,
         1.0,  1.0, -1.0, .10f , 0.f , 0.60f ,
        -1.0,  1.0, -1.0, .20f , 0.87f , 0.60f ,
        // side Right 
        1.0f , 1.0 , 1.0 , .45f , .3f , .4f ,
        1.0 , -1.0 , 1.0 , .5f , .8f, .1f , 
        1.0 , -1.0 , -1.0 , .3f , .6f , .0f ,
        1.0 , 1.0 , -1.0 , .45f , .87f , .53f ,
        // left Side
        -1.0f , 1.0 , 1.0 ,  .45f , .23f , .54f ,
        -1.0 , -1.0 , 1.0 ,  .51f , .84f, .81f , 
        -1.0 , -1.0 , -1.0 ,  .6f , .4f , .78f ,
        -1.0 , 1.0 , -1.0 , .45f , .87f , .53f ,
        //top
        -1.f , 1.f , 1.f , .35f , .87f , .54f ,
        -1.f , 1.f , -1.f , .45f , .98f, .92f ,
        1.f , 1.f , 1.f , .50f , 0.f , .32f  , 
        1.f , 1.f , -1.f , 1.f , .72f , .87f ,
        // bottom
        -1.f , -1.f , 1.f , .35f , .87f , .54f ,
        -1.f , -1.f , -1.f , .45f , .98f, .92f ,
        1.f , -1.f , 1.f , .50f , .89f , .32f  , 
        1.f , -1.f , -1.f , 0.f , .72f , .87f 
    };

    uint32_t indices[] = { 
        0 ,  1 ,  2 ,  0 ,  2 ,  3 ,
        4 ,  5 ,  6 ,  4 ,  6 ,  7 ,
        8 , 9 , 10 , 8 , 10 , 11 ,
        12 , 13 , 14 , 12 , 14 , 15  ,
        16 , 19 , 18 , 16 , 17 , 19 ,
        20 , 23 , 22 , 20 , 21 , 23
    };

    Quack::GPUBuffer::Layout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float3, "a_Color" }
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

    std::shared_ptr<Quack::GPUShader> shader = Quack::Application::GetInstance().GetAssetLibrary().LoadShader("cube.glsl");

    vao->Bind();
    
    shader->Bind();
    shader->UploadUniformMat4f("u_ViewProj", Quack::Application::GetInstance().GetCamera()->GetViewProj());

    Quack::Application::GetInstance().GetDevice()->DrawIndexed(sizeof(indices) / sizeof(uint32_t));
}

void Quack::Renderer::RenderModel(const std::shared_ptr<Quack::Model>& model, const Quack::DirectionalLight& light,
                                  const Mat4f& transform) {
    model->GetIBO()->Bind();
    model->GetVAO()->Bind();

    model->GetShader()->Bind();
    model->GetShader()->UploadUniformMat4f("u_ViewProj", Quack::Application::GetInstance().GetCamera()->GetViewProj());
    model->GetShader()->UploadUniformVec3f("u_Color", (Quack::Vector3f{1.0f, 0.0f, 0.0f}));

    model->GetShader()->UploadUniformVec3f("light.Color", light.GetColor());
    model->GetShader()->UploadUniformFloat("light.Intensity", light.GetIntensity());
    model->GetShader()->UploadUniformVec3f("light.Direction", light.GetLocal());

    // std::shared_ptr<Quack::GPUTexture> texture = Quack::Application::GetInstance().GetAssetLibrary().LoadTexture("western_red_cedar.jpg");
    // texture->Bind();

    for (const auto& mesh : model->GetSubmeshes()) {
        model->GetTextures()[mesh.MaterialIndex]->Bind();
        glDrawElementsBaseVertex(GL_TRIANGLES, mesh.NumIndex, GL_UNSIGNED_INT,
            (void*)(sizeof(uint32_t) * mesh.BaseIndex), mesh.BaseVertex);
    }

}

// void Quack::Renderer::RenderVk(Quack::GPUCommandBufferVulkan* commandBuffer, Quack::GPURenderPassVulkan* renderPass,
//     Quack::GPUPipelineVulkan* pipeline)
// {
//     commandBuffer->Reset();
//     commandBuffer->Begin();
//     // renderPass->Begin();

//     pipeline->BindVk();
//     // vkCmdDraw();
    
//     // renderPass->End();
//     commandBuffer->End();
// }