#ifndef TEXTHANDLER_HPP_
#define TEXTHANDLER_HPP_

// OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Std
#include <string>
#include <stdexcept>
#include <map>
// Libs
#include "ft2build.h"
#include FT_FREETYPE_H
#include "mat4x4.hpp"
#include "gtc/matrix_transform.hpp"
// Custom
#include "util/vector3.hpp"

class TextHandler {
 private:
  const std::string fontPath_ = "assets/fonts/";

  // Mesh Data
  GLuint VBO_, VAO_;
  glm::mat4x4* orthoMatrix_;

  // Character Data
  struct Character {
    GLuint textureID;
    Vector2<int> size;
    Vector2<int> bearing;
    long int advance;
  };
  std::map<GLchar, Character>* charactersAtlas_;

 public:
  TextHandler(const std::string& fontFile, const Vector2<int>& windowSize);
  ~TextHandler();

  void DrawText(const std::string& text, const Vector2<int>& position,
                const float& scale) noexcept;
  const glm::mat4x4* const GetOrthoMatrix() const noexcept;
  const Vector2<float> GetTextSize(const std::string& text,
                                  const float& scale) const noexcept;
};
#endif  // TEXTHANDLER_HPP_