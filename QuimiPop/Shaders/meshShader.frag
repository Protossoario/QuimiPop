#version 330

uniform vec3 materialColor;

out vec4 color;

void main() {
    color = vec4(materialColor, 1.0);
}