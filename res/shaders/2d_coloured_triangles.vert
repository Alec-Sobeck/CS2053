#version 150
  
in vec3 position;
in vec4 color;
out vec4 fragColor;

void main()
{
    fragColor = color;
    gl_Position = vec4(position, 1);
}


