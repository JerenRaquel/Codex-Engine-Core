#version 450

uniform vec3 color;
uniform float alpha;
uniform bool useTexture;
uniform sampler2D tex;

in vec2 v_texcoord;

out vec4 fragColor;

void main() {
    if (useTexture) {
        vec3 color = texture(tex, v_texcoord).xyz;
        float a = texture(tex, v_texcoord).a;
        fragColor = vec4(color, min(alpha, a));
    } else {
        fragColor = vec4(color, alpha);
    }
};