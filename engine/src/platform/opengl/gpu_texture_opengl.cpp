#include "quack/quack.h"
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

Quack::GPUTextureOpenGL::GPUTextureOpenGL(const Quack::GPUTextureDescription & desc) : GPUTexture(desc) {

}

Quack::GPUTextureOpenGL::~GPUTextureOpenGL() {
    glDeleteTextures(1, &_resource);
}

void Quack::GPUTextureOpenGL::Bind() const {
    glBindTextureUnit(0, _resource);
}

void Quack::GPUTextureOpenGL::Unbind() const {
    //glBindTextureUnit(0, _resource);
}
