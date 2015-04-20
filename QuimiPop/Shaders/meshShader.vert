#version 330

in vec3 vertexPosition;
in vec2 vertexUV;
in vec3 vertexNormal;

uniform mat4 transform;
uniform mat4 projection;

out vec2 fragmentUV;

void main() {
    gl_Position = projection * transform * vec4(vertexPosition, 1.0);

    fragmentUV = vertexUV;
}