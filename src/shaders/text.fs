#version 450

in vec2 TexCoords;

uniform sampler2D text;
uniform vec3 textColor;

out vec4 fragColor;

void main() {  
	float alpha = texture(text, TexCoords).r;
	if (alpha == 0.0) {
		discard;
	} else {
		fragColor = vec4(textColor, alpha);
	}
};