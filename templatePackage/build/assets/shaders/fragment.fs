#version 450

uniform vec3 color;
uniform int useTexture;
// x: width cell length, y: height cell length, z: index
uniform ivec3 uvInfo;
uniform sampler2D texture1;

in vec2 TexCoords;

out vec4 fragColor;

vec2 getUV() {
    vec2 uv = TexCoords;
    int xIndex = uvInfo.z % uvInfo.x;
    int yIndex = uvInfo.z / uvInfo.x;

    uv.x = uv.x * uvInfo.x + float(xIndex);
    uv.y = uv.y * uvInfo.y + float(yIndex);
    return uv;
}

void main() {
    vec4 normColor = vec4(color, 1.0) * 1-useTexture;
    vec4 texColor = texture(texture1, getUV()) * useTexture;
    fragColor = normColor + texColor;
};