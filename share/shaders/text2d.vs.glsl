#version 330 core

layout(location = 0) in vec2 vertex;

uniform mat3 MVP;

out vec2 texCoord;


void main() {
    texCoord = vertex;
    vec3 pos = MVP * vec3(vertex,1);
    gl_Position = vec4(pos,1);
}
