#include "../headers/renderEngine.hpp"

RenderEngine::RenderEngine(const Vector<int>& size, const std::string& name) {
  // Initalize GLFW
  if (!glfwInit()) {
    // throw FailedError("ERROR: Couldn't Initialize GLFW...");
    throw std::runtime_error("ERROR: Couldn't Initialize GLFW...");
  }

  // Create a window and set the context
  this->window_ = glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL);
  glfwMakeContextCurrent(this->window_);

  // Initialize GLEW
  GLuint errCode = glewInit();
  if (errCode != GLEW_OK) {
    glfwTerminate();
    // throw FailedError("Error: Unable to Initialize GLEW...");
    throw std::runtime_error("Error: Unable to Initialize GLEW...");
  }

  // Get Versions
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << "\nOpenGL version supported "
            << version << std::endl;

  // Draw pixels if close to the viewer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  this->quads_ = new std::vector<Quad*>();
}

RenderEngine::~RenderEngine() {
  for (unsigned int i = 0; i < this->quads_->size(); i++) {
    delete this->quads_->at(i);
  }
  delete this->quads_;

  glfwTerminate();
}

void RenderEngine::Start() {
  while (!glfwWindowShouldClose(this->window_)) {
    //* Clear Drawing Surface
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //* Draw Calls
    for (unsigned int i = 0; i < this->quads_->size(); i++) {
      this->quads_->at(i)->Draw();
    }

    // // Update the Shader Data
    // this->mesh_->UpdateShaderValues();
    // // Load Active Shader
    // this->mesh_->UseShader();

    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(this->window_);
  }
}

void RenderEngine::AddQuad(Quad* quad) { this->quads_->push_back(quad); }
