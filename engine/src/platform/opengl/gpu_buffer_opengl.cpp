#include "quack/platform/opengl/gpu_buffer_opengl.h"

#include <GL/glew.h>

static GLenum BufferTypeToOpenGLType(Quack::BufferType type) {
    switch (type) {
        case Quack::BufferType::Vertex:
            return GL_ARRAY_BUFFER;
        case Quack::BufferType::Index:
            return GL_ELEMENT_ARRAY_BUFFER;
    }
}

Quack::GPUBufferOpenGL::GPUBufferOpenGL(const Quack::GPUBuffer::Description & desc)
    : GPUBuffer(desc)
{
    glGenBuffers(1, &_resource);
    glBindBuffer(BufferTypeToOpenGLType(desc.Type), _resource);

    // TODO
    glBufferData(BufferTypeToOpenGLType(desc.Type), _desc.Size, _desc.Data, GL_STATIC_DRAW);
}

Quack::GPUBufferOpenGL::~GPUBufferOpenGL() {
    glDeleteBuffers(1, &_resource);
}

void Quack::GPUBufferOpenGL::Bind() const {
    glBindBuffer(BufferTypeToOpenGLType(_desc.Type), _resource);
}

void Quack::GPUBufferOpenGL::Unbind() const {
    glBindBuffer(BufferTypeToOpenGLType(_desc.Type), 0);
}