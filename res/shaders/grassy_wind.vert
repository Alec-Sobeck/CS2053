#version 150
 
uniform mat4 modelMatrix, viewMatrix, projMatrix;
uniform sampler2D texture1;
 
in vec3 position;
in vec4 color;
in vec2 textureIn;
in vec3 normal;
out vec4 fragColor;
out vec2 textureCoord;

uniform vec3 windDirection;
uniform float windPower;

void main()
{
	textureCoord = textureIn;
    fragColor = color;

	vec4 temp = vec4(position, 1.0f);
	if(color.x < 0.1f || color.y < 0.1f || color.z < 0.1f)
	{
		temp += vec4(windDirection.x * windPower, windDirection.y * windPower, windDirection.z * windPower, 0.0f);
	}
    gl_Position = projMatrix * viewMatrix * modelMatrix * temp;
}


