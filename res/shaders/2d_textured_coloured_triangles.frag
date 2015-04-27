#version 150
 
in vec4 fragColor;
in vec2 textureCoord;
uniform sampler2D texture1;
out vec4 outputF;

void main() 
{
    vec4 val = texture(texture1, textureCoord);
    if(val.w >= 0.05f)
    {
	    outputF = val;
    }
    else
    {
	    // Simulate this legacy gl code:	
		// glAlphaFunc(GL_GREATER, 0.05f);
		// glEnable(GL_ALPHA_TEST);
    	discard;
    }
}