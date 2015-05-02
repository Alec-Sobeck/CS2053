#version 150
 
uniform mat4 modelMatrix, viewMatrix, projMatrix;
uniform sampler2D texture1;
 
in vec3 position;
in vec4 color;
in vec3 normal;
in vec2 textureIn;
out vec4 fragColor;
out vec2 textureCoord;
out vec3 fragNormal;

void main()
{
	textureCoord = textureIn;
    fragColor = color;
    fragNormal = normal;
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
}


