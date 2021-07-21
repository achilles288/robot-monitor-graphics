#version 330 core

in vec2 texCoord;

uniform sampler2D image;
uniform vec4 color;

out vec4 fragColor;

void main() {
    fragColor = color * texture(image, texCoord);
}
