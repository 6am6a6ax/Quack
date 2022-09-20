#ifndef QUACK_GPU_BUFFER_H
#define QUACK_GPU_BUFFER_H

#include <string>
#include <vector>

#include "gpu_resource.h"

namespace Quack {
enum class BufferType {
    Vertex, Index
};

class GPUBuffer : public GPUResource {
public:
    class Element;

    class Layout {
    public:
        Layout(const std::initializer_list<Element> &);

    public:
        using Iterator = std::vector<GPUBuffer::Element>::iterator;
        using ConstIterator = std::vector<GPUBuffer::Element>::const_iterator;

    public:
        std::vector<GPUBuffer::Element>::iterator begin();
        std::vector<GPUBuffer::Element>::iterator end();

        std::vector<GPUBuffer::Element>::const_iterator cbegin() const;
        std::vector<GPUBuffer::Element>::const_iterator cend() const;

    public:
        const std::vector<GPUBuffer::Element> & GetElements() const;
        void SetElements(const std::vector<GPUBuffer::Element> &);
        const uint32_t & GetStride() const;

        void SetStride(const uint32_t &);

    private:
        void CalculateOffsetAndStride();

    private:
        std::vector<GPUBuffer::Element> _elements;
        uint32_t _stride;
    };

    struct Description {
        Description() : LayoutDesc({}) {
        }

        void * Data{};

        uint32_t Size{};
        uint32_t Stride{};

        BufferType Type;

        Layout LayoutDesc;

    };

public:
    explicit GPUBuffer(const Description & desc);

public:
    void * GetData() const;
    void SetData(void *);

    const uint32_t & GetSize() const;
    void SetSize(const uint32_t &);

    const uint32_t & GetStride() const;
    void SetStride(const uint32_t &);

    const Layout & GetLayout() const;
    void SetLayout(const Layout &);

    uint32_t GetElementsCount() const;

    const Description & GetDescription() const;
    void SetDescription(const Description &);

protected:
    Description _desc;
};

enum class ShaderDataType {
    None,
    Float, Float2, Float3, Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Bool
};

static uint32_t ShaderDataTypeSize(ShaderDataType);

class GPUBuffer::Element {
public:
    Element(ShaderDataType, const std::string &);

    uint32_t GetComponentCount() const;
public:
    const std::string & GetName() const;
    void SetName(const std::string &);

    const ShaderDataType & GetDataType() const;
    void SetDataType(const ShaderDataType &);

    const uint32_t & GetSize() const;
    void SetSize(const uint32_t &);

    const size_t & GetOffset() const;
    void SetOffset(const size_t &);

    bool IsNormalized() const;

private:
    std::string _name;
    ShaderDataType _dataType;
    uint32_t _size;
    size_t _offset;
    bool _isNormalized;
};
}

#endif