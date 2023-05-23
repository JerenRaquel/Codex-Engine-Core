#include "../headers/shader.hpp"

Shader::Shader(ShaderCompiler* compiler, const std::string& vertexFile,
               const std::string& fragmentFile) {
  this->uniformData_ = new std::map<const char*, Data*>();
  this->shaderIDs_ = new std::vector<const char*>();
  compiler->LoadShaders(vertexFile, fragmentFile);
  compiler->CompileShader(this->shaderID_);
}

Shader::~Shader() {
  for (unsigned int i = 0; i < this->shaderIDs_->size(); i++) {
    Data* d = this->uniformData_->at(this->shaderIDs_->at(i));
    delete d->data;
    delete d;
  }
  delete this->uniformData_;
  delete this->shaderIDs_;
  glDeleteProgram(this->shaderID_);
}

void Shader::PassUniformData() noexcept {
  for (unsigned int i = 0; i < this->shaderIDs_->size(); i++) {
    Data* d = this->uniformData_->at(this->shaderIDs_->at(i));
    GLuint ID = glGetUniformLocation(this->shaderID_, this->shaderIDs_->at(i));
    switch (d->amount) {
      case 1:
        glUniform1f(ID, d->data[0]);
        break;
      case 2:
        glUniform2f(ID, d->data[0], d->data[1]);
        break;
      case 3:
        glUniform3f(ID, d->data[0], d->data[1], d->data[2]);
        break;
      case 4:
        glUniform4f(ID, d->data[0], d->data[1], d->data[2], d->data[3]);
        break;
    }
  }
}

void Shader::AddUniformDataID(const char* variableName, float* data,
                              unsigned int amount) {
  if (this->uniformData_->count(variableName)) {
    return;
  } else {
    this->shaderIDs_->push_back(variableName);
    this->uniformData_->insert(
        std::pair<const char*, Data*>(variableName, new Data{data, amount}));
  }
}

void Shader::UpdateUniformData1f(const char* variableName, float data) {
  if (!this->uniformData_->count(variableName)) {
    return;
  } else {
    delete this->uniformData_->at(variableName)->data;
    this->uniformData_->at(variableName)->data = new float[1]{data};
  }
}

void Shader::UpdateUniformData2f(const char* variableName, float* data) {
  if (!this->uniformData_->count(variableName)) {
    return;
  } else {
    delete this->uniformData_->at(variableName)->data;
    this->uniformData_->at(variableName)->data = data;
  }
}

void Shader::UpdateUniformData3f(const char* variableName, float* data) {
  if (!this->uniformData_->count(variableName)) {
    return;
  } else {
    delete this->uniformData_->at(variableName)->data;
    this->uniformData_->at(variableName)->data = data;
  }
}

void Shader::Use() noexcept { glUseProgram(this->shaderID_); }

GLuint* Shader::GetProgram() noexcept { return &this->shaderID_; }
