#include "../headers/computeShaderCompiler.hpp"

void ComputeShaderCompiler::ValidateShader(GLuint shaderID) const noexcept {
  static const unsigned int bufferSize = 512;
  char buffer[bufferSize];
  GLsizei length = 0;

  glGetShaderInfoLog(shaderID, bufferSize, &length, buffer);

  if (length > 0) {
    std::cout << "ERROR::Compute::Shader failed to compile: " << buffer
              << std::endl;
  }
}

ComputeShaderCompiler::ComputeShaderCompiler() {}

ComputeShaderCompiler::~ComputeShaderCompiler() {}

void ComputeShaderCompiler::LoadShader(const std::string& computeFile) {
  if (computeFile == "") {
    throw std::invalid_argument("ERROR: Unable to read from files...");
  }

  std::string buffer = "";
  std::string computeContent = "";
  std::ifstream computeStream(this->shaderPath_ + computeFile, std::ios::in);

  if (!computeStream.is_open()) {
    std::string message("Error: Unable to open compute file: ");
    message.append(this->shaderPath_ + computeFile);
    throw std::runtime_error(message);
  }

  while (!computeStream.eof()) {
    std::getline(computeStream, buffer);
    computeContent.append(buffer + '\n');
  }

  computeStream.close();
  this->computeShader_ = computeContent;
}

void ComputeShaderCompiler::CompileShader(GLuint& shaderProgram) {
  GLuint computeShader = glCreateShader(GL_COMPUTE_SHADER);
  std::vector<const GLchar*> shaderSource = {this->computeShader_.c_str()};
  glShaderSource(computeShader, 1, &shaderSource[0], NULL);
  glCompileShader(computeShader);
  ValidateShader(computeShader);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, computeShader);
  glLinkProgram(shaderProgram);

  int success = 0;
  char* infoLog = nullptr;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::Compute::Shader failed to link: " << infoLog
              << std::endl;
  }

  // Clean up
  glDeleteShader(computeShader);
}
