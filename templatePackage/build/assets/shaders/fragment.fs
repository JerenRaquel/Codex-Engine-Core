#version 450

uniform vec3 color;
uniform int useTexture;
// x: width cell length, y: height cell length, z: x offset, w: y offset 
uniform vec4 uvInfo;
uniform sampler2D texture1;

in vec2 TexCoords;

out vec4 fragColor;

vec2 getUV() {
    vec2 uv = TexCoords;
    uv.x = uv.x * uvInfo.x + uvInfo.z;
    uv.y = uv.y * uvInfo.y + uvInfo.w;
    return uv;
}

void main() {
    vec4 normColor = vec4(color, 1.0) * 1-useTexture
    vec4 texColor = texture(texture1, getUV) * useTexture;
    fragColor = normColor + texColor;
};