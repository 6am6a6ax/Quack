#include "quack/quack.h"

namespace Quack {
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
                return GL_FLOAT;
            case ShaderDataType::Float2:
                return GL_FLOAT;
            case ShaderDataType::Float3:
                return GL_FLOAT;
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
                return GL_FLOAT;
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
                return GL_INT;
            case ShaderDataType::Int2:
                return GL_INT;
            case ShaderDataType::Int3:
                return GL_INT;
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
        }
    }
}

Quack::GPUVertexArrayOpenGL::GPUVertexArrayOpenGL() {
    glCreateVertexArrays(1, &_resource);
}

Quack::GPUVertexArrayOpenGL::~GPUVertexArrayOpenGL() {
    glDeleteVertexArrays(1, &_resource);
}

void Quack::GPUVertexArrayOpenGL::Bind() const {
    glBindVertexArray(_resource);
}
void Quack::GPUVertexArrayOpenGL::Unbind() const {
    glBindVertexArray(0);
}

void Quack::GPUVertexArrayOpenGL::AddBuffer(const GPUBuffer & buffer) {
    Bind();
    buffer.Bind();
    SetBufferLayout(buffer.GetLayout());
}

void Quack::GPUVertexArrayOpenGL::SetBufferLayout(const GPUBuffer::Layout & layout) {
    uint32_t index = 0;
    for (GPUBuffer::Layout::ConstIterator it = layout.cbegin(); it != layout.cend(); ++it) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
                index,
                it->GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(it->GetDataType()),
                it->IsNormalized() ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void *)(it->GetOffset())
        );
        index++;
    }
}