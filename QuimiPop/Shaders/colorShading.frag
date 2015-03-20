#version 330
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

//This is the 4 component float vector that gets outputted to the screen
//for each pixel.
out vec4 color;

uniform float time;
uniform sampler2D mySampler;

void main() {
    vec4 textureColor = texture(mySampler, fragmentUV);
    
    color = textureColor * fragmentColor;
    color *= vec4(fragmentColor.r * (cos((fragmentUV.x * fragmentUV.y + time) * 1.5) + 3.5) * 0.25,
                  fragmentColor.g * (cos((fragmentUV.x * fragmentUV.y + time) * 1.5) + 3.5) * 0.25,
                  fragmentColor.b * (cos((fragmentUV.x * fragmentUV.y + time) * 1.5) + 3.5) * 0.25,
                  fragmentColor.a);
}