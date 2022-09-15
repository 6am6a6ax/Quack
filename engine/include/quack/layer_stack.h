#ifndef QUACK_LAYER_STACK_H
#define QUACK_LAYER_STACK_H

#include <vector>
#include <memory>

#include "layer.h"

#ifdef TODO
namespace Quack {
class LayerStack {
public:
    LayerStack() : _size(0), _space(0),  _elements(nullptr) {}

    explicit LayerStack(size_t size) :
        _size(size),
        _space(size),
        _elements(new std::shared_ptr<Layer>[size])
    {
        for (int i = 0; i < _size; ++i) {
            _elements[i] = std::make_shared<Layer>();
        }
    }

    explicit LayerStack(const std::shared_ptr<Layer> & layer, size_t size) :
        _size(size),
        _space(size),
        _elements(new std::shared_ptr<Layer>[size])
    {
        for (int i = 0; i < _size; ++i) {
            _elements[i] = layer;
        }
    }

    LayerStack(const LayerStack &) = default;
    LayerStack(LayerStack &) = default;

    LayerStack & operator=(const LayerStack &) = default;
    LayerStack & operator=(LayerStack &) = default;

    ~LayerStack() = default;

public:
    class Iterator;

    Iterator Begin() {}
    const Iterator Begin() {}

    Iterator End() {}
    const Iterator End() {}

    const Iterator cBegin() {}
    const Iterator cEnd() {}

public:
    bool IsEmpty() const {}
    size_t GetCapacity() const {}

    size_t GetSize() const {}
    size_t GetMaxSize() const {}

    void Reserve(int size) {}
    void Resize(int size, const std::shared_ptr<Layer> & = std::move(std::shared_ptr<Layer>())) {}

    void ShrinkToFit() {}

public:
    void Clear() {}

    void PushBack(std::shared_ptr<Layer> & layer) {}
    void PopBack();

public:
    std::shared_ptr<Layer> At(int n) {}
    std::shared_ptr<Layer> operator[](int i) {}

    std::shared_ptr<Layer> Front() {}
    std::shared_ptr<Layer> Back() {}

    Layer * Data() {}
    const Layer * Data() const {}

private:
    size_t _size;
    size_t _space;

    std::shared_ptr<Layer> * _elements;
};

class LayerStack::Iterator {
public:
    Iterator(std::shared_ptr<Layer> * ptr) : _curr(ptr) {}

    Iterator & operator++() {
        _curr++;
        return *this;
    }

    Iterator & operator--() {
        _curr--;
        return  *this;
    }

    std::shared_ptr<Layer> operator*() const {
        return *_curr;
    }

    bool operator==(const Iterator & r) const {
        return *_curr == *(r._curr);
    }

    bool operator!=(const Iterator & r) const {
        return *_curr != *(r._curr);
    }

private:
    std::shared_ptr<Layer> * _curr;
};
}
#endif

namespace Quack {
class LayerStack {
public:
    using Iterator = std::vector<std::shared_ptr<Layer>>::iterator;

public:
    void Push(std::shared_ptr<Layer> layer) {
        layer->OnAttach();
        _elements.push_back(std::forward<std::shared_ptr<Layer>>(layer));
    }

    void Pop(std::shared_ptr<Layer> layer) {
        layer->OnDetach();
        for (auto it = _elements.begin(); it != _elements.end(); ++it) {
            if (*it == layer) {
                _elements.erase(it, it);
            }
        }
    }

public:
    Iterator begin() { return _elements.begin(); }
    Iterator end() { return _elements.end(); }

private:
    std::vector<std::shared_ptr<Layer>> _elements;
};
}

#endif
