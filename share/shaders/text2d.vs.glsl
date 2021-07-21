#version 330 core

layout(location = 0) in vec4 vertex;

uniform mat3 model;

out vec2 texCoord;


void main() {
    texCoord = vertex.zw;
    vec3 pos = model * vec3(vertex.xy,0);
    gl_Position = vec4(pos,1);
}
