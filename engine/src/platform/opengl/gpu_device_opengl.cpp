#include "quack/graphics/gpu_framebuffer.h"
#include "quack/graphics/gpu_texture.h"
#include "quack/graphics/gpu_vertex_array.h"
#include "quack/math/math.h"
#include "quack/platform/opengl/gpu_texture_opengl.h"
#include "quack/quack.h"
#include <GL/gl.h>
#include <memory>

std::shared_ptr<Quack::GPUBuffer> Quack::GPUDeviceOpenGL::CreateBuffer(
        const GPUBuffer::Description& desc) const 
{
    return std::make_shared<Quack::GPUBufferOpenGL>(desc);
}

std::shared_ptr<Quack::GPUShader> Quack::GPUDeviceOpenGL::CreateShader(
        const Quack::GPUShaderDescription& desc) const 
{
    return std::make_shared<Quack::GPUShaderOpenGL>(desc);
}

std::shared_ptr<Quack::GPUShaderProgram> Quack::GPUDeviceOpenGL::CreateShaderProgram(
        const Quack::GPUShaderProgramDescription& desc) const
{
    return std::make_shared<Quack::GPUShaderProgramOpenGL>(desc);
}

std::shared_ptr<Quack::GPUVertexArray> Quack::GPUDeviceOpenGL::CreateVertexArray() const {
    return std::make_shared<Quack::GPUVertexArrayOpenGL>();
}

std::shared_ptr<Quack::GPUTexture> Quack::GPUDeviceOpenGL::CreateTexture(
        const GPUTextureDescription& desc) const 
{
    return std::make_shared<Quack::GPUTextureOpenGL>(desc);
}

std::shared_ptr<Quack::GPUFramebuffer> Quack::GPUDeviceOpenGL::CreateFramebuffer(
        const Quack::GPUFramebufferDescription& desc) const 
{
    return std::make_shared<Quack::GPUFramebufferOpenGL>(desc);
}

void Quack::GPUDeviceOpenGL::Enable(Quack::GPUDevice::CommonFlag flag) const {
    switch (flag) {
        case Quack::GPUDevice::CommonFlag::DEPTH_TEST: return glEnable(GL_DEPTH_TEST); 
    }
}

void Quack::GPUDeviceOpenGL::Disable(Quack::GPUDevice::CommonFlag flag) const {
    switch (flag) {
        case Quack::GPUDevice::CommonFlag::DEPTH_TEST: return glDisable(GL_DEPTH_TEST); 
    }
}

void Quack::GPUDeviceOpenGL::SetDepthFunc(Quack::GPUDevice::DepthFuncFlag flag) const {
    switch (flag) {
        case Quack::GPUDevice::DepthFuncFlag::LESS: return glDepthFunc(GL_LESS); 
    }
}

void Quack::GPUDeviceOpenGL::Clear(Quack::GPUDevice::ClearFlag flag) const {
    switch (flag) {
        case Quack::GPUDevice::ClearFlag::COLOR_BUFFER: return glClear(GL_COLOR_BUFFER_BIT); 
        case Quack::GPUDevice::ClearFlag::DEPTH_BUFFER: return glClear(GL_DEPTH_BUFFER_BIT); 
    }
}
void Quack::GPUDeviceOpenGL::ClearColor(const Quack::Vector4f& color) const {
    glClearColor(color.r, color.g, color.b, color.a);
}

void Quack::GPUDeviceOpenGL::DrawIndexed(uint32_t count) const {
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}