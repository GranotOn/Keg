#version 460 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec4 Color;
uniform sampler2D aTexture;

void main()
{
    FragColor = texture(aTexture, texCoord) * Color;
}