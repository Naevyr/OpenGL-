#version 430 core


layout(local_size_x = 1,local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D u_input;
layout(rgba32f, binding = 1) uniform image2D u_Output;

void main(){
    imageStore(u_Output, ivec2(gl_GlobalInvocationID.xy), vec4(0.0,0.0,1.0,005.0));
}