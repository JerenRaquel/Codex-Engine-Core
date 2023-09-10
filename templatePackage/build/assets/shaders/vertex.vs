#version 450

uniform mat4 mvp;

in vec3 position;
in vec2 uvs;

out vec2 TexCoords;

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    TexCoords = uvs;
};