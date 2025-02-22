
#version 430 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;


void main()
{
    TexCoords = aPos;
    gl_Position = u_Projection * u_View * u_Model * vec4(aPos,1.0);
}  