#version 150
 
in vec3 Color;
in vec2 textureCoord;
uniform sampler2D texture1;
out vec4 outputF;

void main() 
{
    outputF = texture(texture1, textureCoord);
}