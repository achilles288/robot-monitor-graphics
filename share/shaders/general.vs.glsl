#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 shadowMVP;
uniform vec3 scale;
uniform int vflags;

out vec3 normalCamera;
out vec3 eyeDirection;
out vec3 shadowMapProj;
out vec2 texUV;
flat out int flags;


void main() {
    flags = vflags;
    
    normalCamera = (MV * vec4(normal,0)).xyz;
    normalCamera.x /= scale.x;
    normalCamera.y /= scale.y;
    normalCamera.z /= scale.z;
    
    vec3 vertexCamera = (MV * vec4(vertex,1)).xyz;
    eyeDirection = normalize(vec3(0,0,0) - vertexCamera);
    gl_Position = MVP * vec4(vertex,1);
    
    if(bool(flags & (1 << 0))) // Shadow option
        shadowMapProj = (shadowMVP * vec4(vertex,1)).xyz;
    if(bool(flags & (1 << 8))) // Texture option
        texUV = texCoord;
}
