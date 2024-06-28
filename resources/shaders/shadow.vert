#version 430 
layout(location = 0) in vec3 aPos;

uniform mat4 u_LightSpace;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_LightSpace * u_Model * vec4(aPos, 1.0);
}