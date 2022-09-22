#include "quack/platform/opengl/gpu_device_opengl.h"

#include "quack/platform/opengl/gpu_buffer_opengl.h"
#include "quack/platform/opengl/gpu_vertex_array_opengl.h"
#include "quack/platform/opengl/gpu_shader_opengl.h"
#include "quack/platform/opengl/gpu_shader_program_opengl.h"
#include "quack/platform/opengl/gpu_texture_opengl.h"
#include "quack/platform/opengl/gpu_framebuffer_opengl.h"

Quack::GPUBuffer * Quack::GPUDeviceOpenGL::CreateBuffer(const GPUBuffer::Description & desc) const {
    return new Quack::GPUBufferOpenGL(desc);
}

Quack::GPUShader * Quack::GPUDeviceOpenGL::CreateShader(const Quack::GPUShaderDescription & desc) const {
    return new Quack::GPUShaderOpenGL(desc);
}

Quack::GPUShaderProgram * Quack::GPUDeviceOpenGL::CreateShaderProgram(
        const Quack::GPUShaderProgramDescription & desc) const
{
    return new Quack::GPUShaderProgramOpenGL(desc);
}

Quack::GPUVertexArray *Quack::GPUDeviceOpenGL::CreateVertexArray() const {
    return new Quack::GPUVertexArrayOpenGL();
}

Quack::GPUTexture *Quack::GPUDeviceOpenGL::CreateTexture(const GPUTextureDescription & desc) const {
    return new Quack::GPUTextureOpenGL(desc);
}

Quack::GPUFramebuffer * Quack::GPUDeviceOpenGL::CreateFramebuffer(const Quack::GPUFramebufferDescription & desc) const {
    return new Quack::GPUFramebufferOpenGL(desc);
}
