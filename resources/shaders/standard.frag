#version 430
out vec4 FragColor;


in vec3 Normal;
in vec2 TexCoords;
in vec4 FragPos; 


struct LightData {  
    mat4 lightSpace;
    vec3 position;
    vec3 color;
    vec3 direction;
    float intensity;
    int type;
};

layout(location = 0) uniform sampler2D u_Albedo;
layout(location = 1) uniform sampler2D u_Normal;

uniform vec4 u_EnvironmentLighting;
layout(location = 2) uniform sampler2DArray u_ShadowMap;
layout(location = 3) uniform samplerCube u_Skybox;


layout(std140) uniform u_Lights {
    uint count;
    LightData lights[20];
};

float ShadowCalculation(mat4 LightSpace, uint shadowMapID)
{



    // Perform perspective divide
    vec4 fragPosLightSpace = LightSpace * FragPos;
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;


    projCoords = projCoords * 0.5 + 0.5; // Transform to [0,1] range

    // Get closest depth value from light's perspective
    float closestDepth = texture(u_ShadowMap, vec3(projCoords.xy,shadowMapID)).r; 

    // Get current depth value
    float currentDepth = projCoords.z;

    // Check whether current fragment is in shadow
    float shadow = currentDepth - 0.00005 > closestDepth ? 1.0 : 0.0;

    return  shadow ;
}

void main()
{

    vec3 norm = normalize(Normal);





    vec3 illumination = vec3(0);
    vec4 albedo = texture(u_Albedo, TexCoords);
    vec4 normal = texture(u_Normal, TexCoords);
    
    
    
    for(uint i = 0; i < count; ++i) {
        
        vec3 direction = normalize(lights[i].position - FragPos.xyz);
        direction.y = -direction.y;
        float shadow = ShadowCalculation(lights[i].lightSpace,i);                       
        illumination +=  albedo.rgb * (max(dot(norm,direction),0.0)  * lights[i].color * lights[i].intensity * (1-shadow));
  
    }


    vec4 color = vec4(illumination,1) + u_EnvironmentLighting * u_EnvironmentLighting.w ; 
    
    

    FragColor = vec4(color.xyz,1);
    //ragColor = texture(albedo, TexCoords);


}