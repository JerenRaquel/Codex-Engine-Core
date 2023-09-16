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
    float w = 1.0 / float(uvInfo.x);
    float h = 1.0 / float(uvInfo.y);

    uv.x = uv.x * w + float(xIndex) * w;
    uv.y = uv.y * h + float(yIndex) * h;

    return uv;
}

void main() {
    vec4 normColor = vec4(color, 1.0) * 1-useTexture;
    vec4 sampledTexture = texture(texture1, getUV());
    if (sampledTexture.a < 0.1) discard; // discard transparent pixels
    vec4 texColor = sampledTexture * useTexture;
    fragColor = normColor + texColor;
};