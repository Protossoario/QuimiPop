#version 330

in vec2 fragmentUV;

uniform sampler2D textureSampler;

out vec4 color;

void main() {
    color = texture2D(textureSampler, fragmentUV);
}