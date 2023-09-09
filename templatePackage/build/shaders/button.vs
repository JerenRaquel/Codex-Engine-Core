#version 450

uniform mat4 mvp;

in vec3 position;
in vec2 texcoord;

out vec2 v_texcoord;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    v_texcoord = texcoord;
};