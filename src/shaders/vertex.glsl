#version 400

uniform mat4 ortho;
uniform mat4 view;
uniform mat4 model;

in vec3 position;

void main() {
    // gl_Position = ortho * view * model * vec4(position, 1.0);
    gl_Position = model * vec4(position, 1.0);
};