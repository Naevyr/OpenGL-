#version 430 core


layout(local_size_x = 1,local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D input;
layout(rgba32f, binding = 1) uniform image2D output;

void main(){
    
}