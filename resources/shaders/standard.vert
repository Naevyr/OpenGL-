#version 430

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec3 i_Normal;
layout (location = 2) in vec2 i_TextCoords;

out vec3 Normal;
out vec2 TexCoords;
out vec4 FragPos; 


uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
  
void main()
{
    gl_Position = u_Projection * u_View * u_Model *  vec4(i_Position,1);
    Normal = i_Normal;
    TexCoords = i_TextCoords;
    FragPos = u_Model * vec4(i_Position, 1.0);
}