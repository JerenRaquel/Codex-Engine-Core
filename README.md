# Codex-Core

A 2D modular engine to be used for various personal projects.

## Goal

This is the core of many modular extentions to be used in various ways. The idea is a "game" engine into several modules that can be added to a project to add more features. Planned modules can be an extention that integrates software like PyTorch or Tensorflow to add AI training capability to the engine or a simulation module for observing different behaviors based on project. This should reduce bloated code if a project doesn't need certain features.

## Features

- Graphical Rendering System using GLFW/Glew
- Custom mesh control and mesh instancing
- Custom UI system and ImGui for additional gui needs
- Texture mapping and texture atlas support
- Compute shader support
- Multiple scene support (Allows for quickswapping of levels/areas)
- Input System

## Modules

- AI/Machine Learning (integration with PyTorch or Tensorflow) [PLANNED]
- Simulation [PLANNED]
- Editor [PLANNED]
- Audio System (ie. Global and proxity) [PLANNED]
- Serialization/Deserialization (ie. Custom class serialization) [PLANNED]
- Embedded scriptable languages (ie. JavaScript, Python, Lua, etc) [PLANNED]

# Important!
- Dynamic and static files for external libraries are not provided at the moment. (subject to change)
- Library Files needed to provide to use
  - Requires 'libfreetype.a' in Codex-Engine-Core/libs/freetype/.
  - Requires 'libglfw3.a' in Codex-Engine-Core/libs/opengl/.
  - Requires 'glew32.dll' in build/.
  - Requires 'BasicCrayon-Regular.ttf' in build/assets/font/. (Custom font file; Can be swapped with different font file.)
    ```c++
    // Line 67 in Engine/impl/engine.cpp
    this->renderer_ =
      new RenderEngine(windowSize, name, "BasicCrayon-Regular.ttf", "Crayon");
    // Edit to
    this->renderer_ =
      new RenderEngine(windowSize, name, "your font file here", "your font name here");
    ```
