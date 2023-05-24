#include "../headers/shaderCompiler.hpp"

void ShaderCompiler::ValidateShader(GLuint shaderID,
                                    const char* shaderType) const noexcept {
  static const unsigned int bufferSize = 512;
  char buffer[bufferSize];
  GLsizei length = 0;

  glGetShaderInfoLog(shaderID, bufferSize, &length, buffer);

  if (length > 0) {
    std::cout << "ERROR: " << shaderType
              << "::shader failed to compile: " << buffer << std::endl;
  }
}

ShaderCompiler::ShaderCompiler() {}

ShaderCompiler::~ShaderCompiler() {}

void ShaderCompiler::LoadShaders(const std::string& vertexFile,
                                 const std::string& fragmentFile) {
  if (vertexFile == "" || fragmentFile == "") {
    throw std::invalid_argument("ERROR: Unable to read from files...");
  }

  std::string buffer = "";

  std::string vertexContent = "";
  std::ifstream vertexStream(this->shaderPath_ + vertexFile, std::ios::in);

  if (!vertexStream.is_open()) {
    std::string message("Error: Unable to open vertex file: ");
    message.append(this->shaderPath_ + vertexFile);
    throw std::runtime_error(message);
  }
  while (!vertexStream.eof()) {
    std::getline(vertexStream, buffer);
    vertexContent.append(buffer + '\n');
  }
  vertexStream.close();

  std::string fragmentContent = "";
  std::ifstream fragmentStream(this->shaderPath_ + fragmentFile, std::ios::in);

  if (!fragmentStream.is_open()) {
    std::string message("Error: Unable to open fragment file: ");
    message.append(this->shaderPath_ + fragmentFile);
    throw std::runtime_error(message);
  }
  while (!fragmentStream.eof()) {
    std::getline(fragmentStream, buffer);
    fragmentContent.append(buffer + '\n');
  }
  fragmentStream.close();

  this->vertexShader_ = vertexContent;
  this->fragmentShader_ = fragmentContent;
}

void ShaderCompiler::CompileShader(GLuint& shaderProgram) {
  //* Load the shaders
  // Vertex Shader Compile
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  std::vector<const GLchar*> vertexShaderSource = {this->vertexShader_.c_str()};
  glShaderSource(vs, 1, &vertexShaderSource[0], NULL);
  glCompileShader(vs);
  ValidateShader(vs, "Vertex Shader");

  // Vertex Fragment Compile
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  std::vector<const GLchar*> fragmentShaderSource = {
      this->fragmentShader_.c_str()};
  glShaderSource(fs, 1, &fragmentShaderSource[0], NULL);
  glCompileShader(fs);
  ValidateShader(fs, "Fragment Shader");

  //* Compile the Shaders into a single program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, fs);
  glAttachShader(shaderProgram, vs);
  glLinkProgram(shaderProgram);
  // check for linking errors
  int success = 0;
  char* infoLog = nullptr;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  //* Clean UP
  glDeleteShader(vs);
  glDeleteShader(fs);
}
