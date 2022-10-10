#include "quack/quack.h"
#include <cstdint>
#include <memory>
#include <string>

Quack::GPUShaderUniformOpenGL::GPUShaderUniformOpenGL(
    Quack::GPUShaderDomain domain,
    Quack::GPUShaderUniformOpenGL::Type type,
    const std::string& name,
    uint32_t count
)
    : _domain(domain),
      _type(type),
      _name(name),
      _struct(nullptr),
      _count(count),
      _offset(0),
      _location(0) 
{
    _size = GetSizeOfType(type) * _count;
}

bool Quack::GPUShaderUniformOpenGL::IsArray() const {
    return (_count > 1);
}

const std::string& Quack::GPUShaderUniformOpenGL::GetName() const {
    return _name;
}

Quack::GPUShaderDomain Quack::GPUShaderUniformOpenGL::GetDomain() const {
    return _domain;
}

uint32_t Quack::GPUShaderUniformOpenGL::GetSize() const {
    return _size;
}

uint32_t Quack::GPUShaderUniformOpenGL::GetCount() const {
    return _count;
}

uint32_t Quack::GPUShaderUniformOpenGL::GetOffset() const {
    return _offset;
}

uint32_t Quack::GPUShaderUniformOpenGL::GetSizeOfType(Type type) {
    switch (type) {
        case Quack::GPUShaderUniformOpenGL::Type::BOOL:    return 1;
        case Quack::GPUShaderUniformOpenGL::Type::INT32:   return 4;
        case Quack::GPUShaderUniformOpenGL::Type::FLOAT32: return 4;
        case Quack::GPUShaderUniformOpenGL::Type::VEC2:    return 4 * 2;
        case Quack::GPUShaderUniformOpenGL::Type::VEC3:    return 4 * 3;
        case Quack::GPUShaderUniformOpenGL::Type::VEC4:    return 4 * 4;
        case Quack::GPUShaderUniformOpenGL::Type::MAT3:    return 4 * 3 * 3;
        case Quack::GPUShaderUniformOpenGL::Type::MAT4:    return 4 * 4 * 4;
    }

    return 0;
}

Quack::GPUShaderUniformOpenGL::Type Quack::GPUShaderUniformOpenGL::GetType() const {
    return _type;
}

int32_t Quack::GPUShaderUniformOpenGL::GetLocation() const {
    return _location;
}

uint32_t Quack::GPUShaderUniformOpenGL::GetAbsoluteOffset() const {
    return (_struct ? _struct->GetOffset() : _offset);
}

const std::shared_ptr<Quack::ShaderStruct>& Quack::GPUShaderUniformOpenGL::GetShaderStruct() const {
    return _struct;
}

void Quack::GPUShaderUniformOpenGL::SetOffset(uint32_t offset) {
    _offset = offset;
}