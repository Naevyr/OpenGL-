
#version 430 core


layout(local_size_x = 1,local_size_y = 1, local_size_z = 1) in;

layout(rgba32f, binding = 0) uniform image2D u_input;
layout(rgba32f, binding = 1) uniform image2D u_Output;

uniform int u_blurSize;


void main() {
    

    vec4 color = vec4(0);
    float weight = 0;

    int blurRadius = u_blurSize / 2;
    for(int x = -blurRadius; x <= blurRadius; x++){
        for(int y = -blurRadius; y <= blurRadius; y++){
            
            ivec2 position = ivec2(x,y) + ivec2(gl_GlobalInvocationID.xy);
            if(position.x < 0 || position.y < 0 || position.x > gl_NumWorkGroups.x || position.y > gl_NumWorkGroups.y)
                continue;


            color += imageLoad(u_input,position);
            weight++;


        }   
    }

    imageStore(u_Output,ivec2(gl_GlobalInvocationID.xy),color / weight);
    
}