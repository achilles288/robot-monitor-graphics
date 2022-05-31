#version 330 core

in vec2 texCoord;

uniform sampler2D font;
uniform vec2 char;
uniform vec2 size;
uniform vec4 color;

out vec4 fragColor;


void main() {
    vec2 v = char + texCoord * size;
    float a = texture(font, v).r * color.w;
    fragColor = vec4(color.xyz, a);
}
