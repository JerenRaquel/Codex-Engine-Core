#include "../headers/renderEngine.hpp"

RenderEngine::RenderEngine(const Vector2& size, const std::string& name) {
  // Initalize GLFW
  if (!glfwInit()) {
    throw FailedError("ERROR: Couldn't Initialize GLFW...");
  }

  // Create a window and set the context
  this->window_ = glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL);
  glfwMakeContextCurrent(this->window_);

  // Initialize GLEW
  GLuint errCode = glewInit();
  if (errCode != GLEW_OK) {
    glfwTerminate();
    throw FailedError("Error: Unable to Initialize GLEW...");
  }

  // Get Versions
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << "\nOpenGL version supported "
            << version << std::endl;

  // Draw pixels if close to the viewer
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

RenderEngine::~RenderEngine() { glfwTerminate(); }

void RenderEngine::Start() {
  while (!glfwWindowShouldClose(this->window_)) {
    //* Clear Drawing Surface
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //* Draw Calls
    // // Update the Shader Data
    // this->mesh_->UpdateShaderValues();
    // // Load Active Shader
    // this->mesh_->UseShader();

    // // Load Active VAO
    // glBindVertexArray(this->mesh_->GetVertexArrayObjectID());
    // // Draw Data
    // glDrawElements(GL_TRIANGLES, this->mesh_->GetPointAmount(),
    // GL_UNSIGNED_INT,
    //                0);

    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(this->window_);
  }
}
