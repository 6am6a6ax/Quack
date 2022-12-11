#include "quack/quack.h"

Quack::GPUBuffer::GPUBuffer(const Quack::GPUBuffer::Description & desc) : _desc(desc) {}

void * Quack::GPUBuffer::GetData() const {
    return _desc.Data;
}

void Quack::GPUBuffer::SetData(void * data) {
    _desc.Data = data;
}

const uint32_t & Quack::GPUBuffer::GetSize() const {
    return _desc.Size;
}

void Quack::GPUBuffer::SetSize(const uint32_t & size) {
    _desc.Size = size;
}

const uint32_t & Quack::GPUBuffer::GetStride() const {
    return _desc.Stride;
}

void Quack::GPUBuffer::SetStride(const uint32_t & stride) {
    _desc.Stride = stride;
}

uint32_t Quack::GPUBuffer::GetElementsCount() const {
    // TODO
    return 3;
}

const Quack::GPUBuffer::Description &Quack::GPUBuffer::GetDescription() const {
    return _desc;
}

void Quack::GPUBuffer::SetDescription(const Quack::GPUBuffer::Description & desc) {
    _desc = desc;
}

const Quack::GPUBuffer::Layout &Quack::GPUBuffer::GetLayout() const {
    return _desc.LayoutDesc;
}

void Quack::GPUBuffer::SetLayout(const Quack::GPUBuffer::Layout & layout) {
    _desc.LayoutDesc = layout;
}


Quack::GPUBuffer::Layout::Layout(const std::initializer_list<GPUBuffer::Element> & elements) : _elements(elements) {
    CalculateOffsetAndStride();
}

std::vector<Quack::GPUBuffer::Element>::iterator Quack::GPUBuffer::Layout::begin() {
    return _elements.begin();
}

std::vector<Quack::GPUBuffer::Element>::iterator Quack::GPUBuffer::Layout::end() {
    return _elements.end();
}

std::vector<Quack::GPUBuffer::Element>::const_iterator Quack::GPUBuffer::Layout::cbegin() const {
    return _elements.cbegin();
}

std::vector<Quack::GPUBuffer::Element>::const_iterator Quack::GPUBuffer::Layout::cend() const {
    return _elements.cend();
}

const std::vector<Quack::GPUBuffer::Element> &Quack::GPUBuffer::Layout::GetElements() const {
    return _elements;
}

void Quack::GPUBuffer::Layout::SetElements(const std::vector<GPUBuffer::Element> & elements) {
    _elements = elements;
}

const uint32_t &Quack::GPUBuffer::Layout::GetStride() const {
    return _stride;
}

void Quack::GPUBuffer::Layout::SetStride(const uint32_t & stride) {
    _stride = stride;
}

void Quack::GPUBuffer::Layout::CalculateOffsetAndStride() {
    size_t offset = 0;
    _stride = 0;
    for (auto & element : _elements) {
        element.SetOffset(offset);
        offset += element.GetSize();
        _stride += element.GetSize();
    }
}

Quack::GPUBuffer::Element::Element(Quack::ShaderDataType dataType, const std::string & name)
    : _name(name),
      _dataType(dataType),
      _size(ShaderDataTypeSize(dataType)),
      _offset(0),
      _isNormalized(false) {}

uint32_t Quack::GPUBuffer::Element::GetComponentCount() const {
    switch (_dataType) {
        case ShaderDataType::Float:  return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;

        case ShaderDataType::Mat3:   return 3;
        case ShaderDataType::Mat4:   return 4;

        case ShaderDataType::Int:    return 1;
        case ShaderDataType::Int2:   return 2;
        case ShaderDataType::Int3:   return 3;
        case ShaderDataType::Int4:   return 4;

        case ShaderDataType::Bool:   return 1;
    }
    
    return 0;
}

const std::string &Quack::GPUBuffer::Element::GetName() const {
    return _name;
}

void Quack::GPUBuffer::Element::SetName(const std::string & name) {
    _name = name;
}

const Quack::ShaderDataType &Quack::GPUBuffer::Element::GetDataType() const {
    return _dataType;
}

void Quack::GPUBuffer::Element::SetDataType(const Quack::ShaderDataType & dataType) {
    _dataType = dataType;
}

const uint32_t &Quack::GPUBuffer::Element::GetSize() const {
    return _size;
}

void Quack::GPUBuffer::Element::SetSize(const uint32_t & size) {
    _size = size;
}

const size_t &Quack::GPUBuffer::Element::GetOffset() const {
    return _offset;
}

void Quack::GPUBuffer::Element::SetOffset(const size_t & offset) {
    _offset = offset;
}

bool Quack::GPUBuffer::Element::IsNormalized() const {
    return _isNormalized;
}

uint32_t Quack::ShaderDataTypeSize(Quack::ShaderDataType type) {
    switch (type)
    {
        case ShaderDataType::Float:    return 4;
        case ShaderDataType::Float2:   return 4 * 2;
        case ShaderDataType::Float3:   return 4 * 3;
        case ShaderDataType::Float4:   return 4 * 4;
        case ShaderDataType::Mat3:     return 4 * 3 * 3;
        case ShaderDataType::Mat4:     return 4 * 4 * 4;
        case ShaderDataType::Int:      return 4;
        case ShaderDataType::Int2:     return 4 * 2;
        case ShaderDataType::Int3:     return 4 * 3;
        case ShaderDataType::Int4:     return 4 * 4;
        case ShaderDataType::Bool:     return 1;
    }

    return 0;
}
