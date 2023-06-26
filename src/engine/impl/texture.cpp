#include "texture.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

Texture::Texture(const std::string& imageFileName) {
  std::string path = this->imagePath_ + imageFileName;

  GLint colorFormat = GL_RGB;
  int stbiColorFormat = 0;
  if (stringEndsWith(imageFileName, ".png")) {
    colorFormat = GL_RGBA;
    stbiColorFormat = STBI_rgb_alpha;
  }
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(path.c_str(), &this->width_, &this->height_,
                                  0, stbiColorFormat);

  if (!data) {
    throw std::runtime_error("Failed to load texture");
  }

  // Create and bind textures
  glGenTextures(1, &this->textureID_);
  glBindTexture(GL_TEXTURE_2D, this->textureID_);

  // Set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Load image data into texture buffer
  glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, this->width_, this->height_, 0,
               colorFormat, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Free image data
  stbi_image_free(data);
  Unbind();
}

Texture::~Texture() {}

void Texture::Bind() const noexcept {
  glBindTexture(GL_TEXTURE_2D, this->textureID_);
}

void Texture::Unbind() const noexcept { glBindTexture(GL_TEXTURE_2D, 0); }
