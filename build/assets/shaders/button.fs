#version 450

uniform vec3 color;
uniform float alpha;
uniform bool useTexture;
uniform bool useBackgroundColor;
uniform sampler2D tex;

in vec2 v_texcoord;

out vec4 fragColor;

void main() {
    if (useTexture) {
        vec3 textColor = texture(tex, v_texcoord).xyz;
        float a = min(alpha,texture(tex, v_texcoord).a);

        if (useBackgroundColor && texture(tex, v_texcoord).a == 0.0) {
            textColor = color;
            a = alpha;
        }

        fragColor = vec4(textColor,  a);
    } else {
        fragColor = vec4(color, alpha);
    }
};