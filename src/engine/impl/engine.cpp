#include "engine.hpp"

#include "../../../tools/tracy/tracy/Tracy.hpp"

void Engine::MoveCamera() noexcept {
  if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_R) == GLFW_PRESS) {
    this->camera_->ResetPosition();
    return;
  }

  Vector<float> direction;
  if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
    direction.y = -1.0f;
  } else if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_S) ==
             GLFW_PRESS) {
    direction.y = 1.0f;
  }

  if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
    direction.x = 1.0f;
  } else if (glfwGetKey(this->renderer_->GetWindow(), GLFW_KEY_D) ==
             GLFW_PRESS) {
    direction.x = -1.0f;
  }
  if (direction.x != 0.0f && direction.y != 0.0f) {
    direction.x *= 0.70710678118f;  // sqrt(2)/2
    direction.y *= 0.70710678118f;
  }
  this->camera_->UpdatePosition(direction);
}

void Engine::CreatePrimativeMeshes() const noexcept {
  float coneVertices[] = {
      0.0f,  2.5f,  0.0f, 0.5f, 1.0f,  // top center
      -2.5f, -2.5f, 0.0f, 0.0f, 0.0f,  // bottom left
      2.5f,  -2.5f, 0.0f, 1.0f, 0.0f   // bottom right
  };
  unsigned int coneIndices[] = {
      0, 1, 2,  // first triangle
  };

  Mesh* coneMesh = new Mesh(coneVertices, 15, coneIndices, 3);
  this->renderer_->AddMeshType("Cone", coneMesh);

  float quadVertices[] = {
      -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  // top left
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
      1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      1.0f,  1.0f,  0.0f, 1.0f, 1.0f   // top right
  };
  unsigned int quadIndices[] = {
      0, 1, 2,  // first triangle
      0, 2, 3,  // second triangle
  };

  Mesh* quadMesh = new Mesh(quadVertices, 20, quadIndices, 6);
  this->renderer_->AddMeshType("Quad", quadMesh);
}

void Engine::Start() {
  // Initilize renderer stuff
  this->renderer_->CompileShader("vertex.vs", "fragment.fs", "default");
  this->renderer_->CompileShader("button.vs", "button.fs", "button");
  this->renderer_->CompileShader("text.vs", "text.fs", "Crayon");
  this->CreatePrimativeMeshes();

  this->mainAction_->OnStart(this);

  if (this->currentScene_ != nullptr) {
    this->currentScene_->Start(this);
  }

  // Main loop
  while (!glfwWindowShouldClose(this->renderer_->GetWindow())) {
    FrameMark;
    this->MoveCamera();
    glm::mat4x4* orthoViewMatrixCached = this->camera_->GetViewOrthoMatrix();
    this->inputSystem_->Update(this->renderer_->GetWindow());

    if (this->currentScene_ != nullptr) {
      this->currentScene_->Update(this);
    }

    this->renderer_->Render(orthoViewMatrixCached, this->currentScene_);

    // update other events like input handling
    glfwPollEvents();
  }
}

Engine::Engine(const Vector<int>& windowSize, const std::string& name,
               const std::vector<std::string>& args, Action* mainAction) {
  this->windowSize_ = windowSize;
  this->args_ = new std::vector<std::string>(args);
  this->renderer_ =
      new RenderEngine(windowSize, name, "BasicCrayon-Regular.ttf", "Crayon");
  this->computeShaderCompiler_ = new ComputeShaderCompiler();
  this->camera_ = new Camera(windowSize, 0.1f, 100.0f);
  this->computeShaders_ = new std::map<std::string, ComputeShader*>();
  this->computeShaderBuffers_ =
      new std::map<std::string, ComputeShaderBuffer*>();
  this->inputSystem_ = new InputSystem(windowSize);
  this->mainAction_ = mainAction;
  this->scenes_ = new std::map<std::string, Scene*>();

  this->Start();
}

Engine::~Engine() {
  delete this->renderer_;
  delete this->computeShaderCompiler_;
  delete this->camera_;
  delete this->computeShaders_;

  for (auto& computeShaderBuffer : *this->computeShaderBuffers_) {
    delete computeShaderBuffer.second;
  }
  delete this->computeShaderBuffers_;

  for (auto scene : *this->scenes_) {
    delete scene.second;
  }
  delete this->scenes_;
}

// Utility

void Engine::CompileComputeShader(const std::string& computeFile,
                                  const std::string& name) const {
  if (this->computeShaders_->count(name) > 0) {
    throw std::runtime_error("Compute shader already exists");
  }

  ComputeShader* computeShader =
      new ComputeShader(this->computeShaderCompiler_, computeFile);
  this->computeShaders_->insert(
      std::pair<std::string, ComputeShader*>(name, computeShader));
}

ComputeShaderBuffer* const Engine::AssignNewComputeShaderBuffer(
    const std::string& name, const unsigned int& width,
    const unsigned int& height) const {
  if (this->computeShaderBuffers_->count(name) > 0) {
    throw std::runtime_error("Compute shader buffer already exists");
  }
  ComputeShaderBuffer* buffer = new ComputeShaderBuffer(width, height);
  this->computeShaderBuffers_->insert(
      std::pair<std::string, ComputeShaderBuffer*>(name, buffer));
  return buffer;
}

Scene* const Engine::AddScene(const std::string& name, Scene* scene) {
  if (this->scenes_->count(name) > 0) {
    throw std::runtime_error("Scene already exists");
  }
  this->scenes_->insert(std::pair<std::string, Scene*>(name, scene));
  if (this->currentScene_ == nullptr) {
    this->currentScene_ = scene;
    this->currentSceneName_ = name;
  }
  return scene;
}

Scene* const Engine::SetCurrentScene(const std::string& name) {
  if (this->currentSceneName_ == name) {
    return this->currentScene_;
  }

  if (this->scenes_->count(name) == 0) {
    throw std::runtime_error("Scene does not exist");
  }
  this->currentScene_ = this->scenes_->at(name);
  this->currentSceneName_ = name;
  this->currentScene_->Start(this);
  return this->currentScene_;
}

// Getters
RenderEngine* const Engine::GetRenderer() const noexcept {
  return this->renderer_;
}

Vector<int> Engine::GetWindowSize() const noexcept { return this->windowSize_; }

std::vector<std::string>* const Engine::GetArgs() const noexcept {
  return this->args_;
}

ComputeShader* const Engine::GetComputeShader(const std::string& name) const {
  if (this->computeShaders_->count(name) == 0) {
    throw std::runtime_error("Compute shader does not exist");
  }
  return this->computeShaders_->at(name);
}

ComputeShaderBuffer* const Engine::GetComputeShaderBuffer(
    const std::string& name) const noexcept {
  if (this->computeShaderBuffers_->count(name) == 0) {
    return nullptr;
  }

  return this->computeShaderBuffers_->at(name);
}

InputSystem* const Engine::GetInputSystem() const noexcept {
  return this->inputSystem_;
}

Scene* const Engine::GetCurrentScene() const noexcept {
  return this->currentScene_;
}
