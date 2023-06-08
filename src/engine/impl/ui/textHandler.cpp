#include "ui/textHandler.hpp"

unsigned TextHandler_MaxWidth_ = 0;
unsigned TextHandler_MaxHeight_ = 0;

TextHandler::TextHandler(const std::string& fontFile,
                         const Vector<int>& windowSize) {
  // Setup FreeType
  FT_Library ft = FT_Library();

  if (FT_Init_FreeType(&ft)) {
    throw std::runtime_error("Could not initialize FreeType library.");
  }

  std::string fontPath = this->fontPath_ + fontFile;
  FT_Face face;
  FT_Error error = FT_New_Face(ft, fontPath.c_str(), 0, &face);
  if (error == FT_Err_Unknown_File_Format) {
    throw std::runtime_error("Font file format not supported.");
  } else if (error) {
    throw std::runtime_error("Could not open font file.");
  }

  if (FT_Set_Pixel_Sizes(face, 0, 48)) {
    throw std::runtime_error("Could not set font size.");
  }

  // Create Texture Atlas
  this->charactersAtlas_ = new std::map<GLchar, Character>();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);  // Disable byte-alignment restriction

  for (GLubyte c = 0; c < 128; c++) {
    FT_Load_Char(face, c, FT_LOAD_RENDER);

    GLuint textureID;
    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
    glTextureStorage2D(textureID, 1, GL_R8, face->glyph->bitmap.width,
                       face->glyph->bitmap.rows);
    glTextureSubImage2D(textureID, 0, 0, 0, face->glyph->bitmap.width,
                        face->glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer);

    glBindTexture(GL_TEXTURE_2D, textureID);
    // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // Set texture filtering to GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (face->glyph->bitmap.width > TextHandler_MaxWidth_) {
      TextHandler_MaxWidth_ = face->glyph->bitmap.width;
    }
    if (face->glyph->bitmap.rows > TextHandler_MaxHeight_) {
      TextHandler_MaxHeight_ = face->glyph->bitmap.rows;
    }

    Character character = {
        textureID,
        Vector<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        Vector<int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x};
    this->charactersAtlas_->insert(std::pair<GLchar, Character>(c, character));
  }
  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  // Setup OpenGL
  glCreateVertexArrays(1, &this->VAO_);
  glBindVertexArray(this->VAO_);

  glCreateBuffers(1, &this->VBO_);

  glNamedBufferStorage(this->VBO_, sizeof(GLfloat) * 6 * 4, NULL,
                       GL_DYNAMIC_STORAGE_BIT);
  glVertexArrayVertexBuffer(this->VAO_, 0, this->VBO_, 0, sizeof(GLfloat) * 4);
  glVertexArrayAttribFormat(this->VAO_, 0, 4, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(this->VAO_, 0, 0);
  glEnableVertexArrayAttrib(this->VAO_, 0);

  this->orthoMatrix_ = new glm::mat4x4();
  glm::mat4x4 orthoTemp = glm::ortho(0.0f, static_cast<float>(windowSize.x),
                                     0.0f, static_cast<float>(windowSize.y));
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      (*(this->orthoMatrix_))[i][j] = orthoTemp[i][j];
    }
  }
}

TextHandler::~TextHandler() {
  delete this->charactersAtlas_;
  delete this->orthoMatrix_;
  glDeleteBuffers(1, &this->VBO_);
  glDeleteVertexArrays(1, &this->VAO_);
}

void TextHandler::DrawText(const std::string& text, const Vector<int>& position,
                           const int& scale) noexcept {
  float x = position.x;
  float y = position.y;

  for (std::string::const_iterator c = text.begin(); c != text.end(); c++) {
    Character ch = this->charactersAtlas_->at(*c);
    float xpos = x + ch.bearing.x * scale;
    float ypos = y - (ch.size.y - ch.bearing.y) * scale;
    float w = ch.size.x * scale;
    float h = ch.size.y * scale;

    GLfloat vertices[6 * 4] = {
        xpos,     ypos + h, 0.0f, 0.0f,  // Bottom left
        xpos,     ypos,     0.0f, 1.0f,  // Top left
        xpos + w, ypos,     1.0f, 1.0f,  // Top right

        xpos,     ypos + h, 0.0f, 0.0f,  // Bottom left
        xpos + w, ypos,     1.0f, 1.0f,  // Top right
        xpos + w, ypos + h, 1.0f, 0.0f   // Bottom right
    };

    glNamedBufferSubData(this->VBO_, 0, sizeof(GLfloat) * 6 * 4, vertices);
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    glBindVertexArray(this->VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    x += (ch.advance >> 6) * scale;
  }
}

const glm::mat4x4* const TextHandler::GetOrthoMatrix() const noexcept {
  return this->orthoMatrix_;
}
