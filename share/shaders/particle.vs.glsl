#version 330 core

layout(location = 0) in vec4 vertex;

uniform vec3 TV;
uniform mat3 model;
uniform mat4 projection;

out vec2 texCoord;


void main() {
    texCoord = vertex.zw;
    vec3 LM = model * vec3(vertex.xy, 1);
    LM.z = 0;
    vec4 LM_TV = vec4(LM + TV, 1);
    gl_Position = projection * LM_TV;
}
