#version 150
 
uniform mat4 viewMatrix, projMatrix;
uniform sampler2D texture1;
 
in vec3 position;
in vec3 color;
in vec2 textureIn;
out vec3 Color;
out vec2 textureCoord;

void main()
{
	textureCoord = textureIn;
    Color = color;
    gl_Position = vec4(position, 1);//projMatrix * viewMatrix * position ;
}


