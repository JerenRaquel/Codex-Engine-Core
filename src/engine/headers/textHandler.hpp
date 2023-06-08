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
#include "vector.hpp"

extern unsigned TextHandler_MaxWidth_;
extern unsigned TextHandler_MaxHeight_;

class TextHandler {
 private:
  const std::string fontPath_ = "assets/fonts/";

  // Mesh Data
  GLuint VBO_, VAO_;
  glm::mat4x4* orthoMatrix_;

  // Character Data
  struct Character {
    GLuint textureID;
    Vector<int> size;
    Vector<int> bearing;
    long int advance;
  };
  std::map<GLchar, Character>* charactersAtlas_;

 public:
  TextHandler(const std::string& fontFile, const Vector<int>& windowSize);
  ~TextHandler();

  void DrawText(const std::string& text, const Vector<int>& position,
                const int& scale) noexcept;
  const glm::mat4x4* const GetOrthoMatrix() const noexcept;
};
#endif  // TEXTHANDLER_HPP_