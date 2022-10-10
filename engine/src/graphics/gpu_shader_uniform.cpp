#include "quack/quack.h"
#include <cstdint>

Quack::ShaderStruct::ShaderStruct(const std::string& name)
    : _name(name),
      _size(0),
      _offset(0),
      _fields(Quack::IGPUShaderUniform::List()) {}

void Quack::ShaderStruct::Push(const std::shared_ptr<IGPUShaderUniform>& field) {
    _size = field->GetSize();
    uint32_t offset = 0;
    if (_fields.size() > 0) {
        const auto& prev = _fields.back();
        offset = prev->GetOffset() + prev->GetSize();
    }
    field->SetOffset(offset);
    _fields.push_back(field);
}

const std::string& Quack::ShaderStruct::GetName() const {
    return _name;
}

uint32_t Quack::ShaderStruct::GetSize() const {
    return _size;
}

uint32_t Quack::ShaderStruct::GetOffset() const {
    return _offset;
}

const Quack::IGPUShaderUniform::List& Quack::ShaderStruct::GetFields() const {
    return _fields;
}

void Quack::ShaderStruct::SetOffset(uint32_t offset) {
    _offset = offset;
}