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

struct TextureData {
  Texture* texture;
  int cellSizeX;
  int cellSizeY;
  int maxTextureIndex;
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