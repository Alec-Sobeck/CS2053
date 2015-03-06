#version 120

uniform vec3 windDirection;
uniform float windPower;

void main() 
{
	vec4 temp = gl_Vertex;

	if(gl_Color.x < 0.1f || gl_Color.y < 0.1f || gl_Color.z < 0.1f)
	{
		temp += vec4(windDirection.x * windPower, windDirection.y * windPower, windDirection.z * windPower, 0.0f);
	}

	gl_Position = gl_ModelViewProjectionMatrix * temp; //Transform the vertex position
    	gl_TexCoord[0] = gl_MultiTexCoord0;

}
