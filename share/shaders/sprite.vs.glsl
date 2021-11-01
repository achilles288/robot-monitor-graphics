#version 330 core

layout(location = 0) in vec4 vertex;

uniform mat3 MVP;

out vec2 texCoord;


void main() {
    texCoord = vertex.zw;
    vec3 pos = MVP * vec3(vertex.xy,1);
    gl_Position = vec4(pos.xy, 0, 1);
}
