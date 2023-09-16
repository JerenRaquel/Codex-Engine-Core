#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <string>
#include <exception>
// Engine
#include "util/helpers.hpp"

class Texture;

class TextureData {
 public:
  Texture* texture;
  int cellSizeX;
  int cellSizeY;
  int maxTextureIndex;

  TextureData()
      : texture(nullptr), cellSizeX(0), cellSizeY(0), maxTextureIndex(0) {}
  TextureData(Texture* texture, const int& cellSizeX, const int& cellSizeY)
      : texture(texture),
        cellSizeX(cellSizeX),
        cellSizeY(cellSizeY),
        maxTextureIndex(cellSizeX * cellSizeY) {}
  ~TextureData() {}
};

class Texture {
 private:
  const std::string imagePath_ = "assets/images/";
  int width_;
  int height_;

  GLuint textureID_;

 public:
  Texture(const std::string& imageFileName);
  ~Texture();

  void Bind() const noexcept;
  void Unbind() const noexcept;
};
#endif  // TEXTURE_HPP_