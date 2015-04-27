#version 150
 
uniform mat4 viewMatrix, projMatrix;
uniform sampler2D texture1;
 
in vec3 position;
in vec4 color;
in vec2 textureIn;
in vec3 normal;
out vec4 fragColor;
out vec2 textureCoord;

void main()
{
	textureCoord = textureIn;
    fragColor = color;
    gl_Position = projMatrix * viewMatrix * vec4(position, 1.0f);
}


