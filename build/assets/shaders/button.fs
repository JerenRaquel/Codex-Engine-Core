#version 450

uniform vec3 color;
uniform float alpha;
uniform bool useTexture;
uniform sampler2D tex;

in vec2 v_texcoord;

out vec4 fragColor;

void main() {
    if (useTexture) {
        fragColor = texture(tex, v_texcoord);
    } else {
        fragColor = vec4(color, alpha);
    }
};