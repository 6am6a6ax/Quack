#include "quack/quack.h"

Quack::GPUShaderProgram::GPUShaderProgram(const Quack::GPUShaderProgramDescription& desc) : _desc(desc) {}

const Quack::GPUShaderProgramDescription& Quack::GPUShaderProgram::GetDescription() const {
    return _desc;
}

const std::shared_ptr<Quack::GPUDevice>& Quack::GPUShaderProgram::GetDevice() const {
    return _desc.Device;
}
