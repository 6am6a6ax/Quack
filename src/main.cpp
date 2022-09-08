#include <iostream>

#include "platform/opengl/gpu_buffer_opengl.hpp"

int main() {
    std::cout << "Hello, World!\n";

    Quack::GPUBufferDescription description;
    description.Size = 1;
    description.Stride = 2;
    description.Usage = Quack::GPUResourceUsage::Default;
    description.Format = Quack::GPUPixelFormat::Unknown;
    description.Utility = Quack::GPUBufferUtility::Unknown;

    Quack::GPUBufferOpenGL buffer = Quack::GPUBufferOpenGL(description);

    buffer.Bind();

    return 0;
}
