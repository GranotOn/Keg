#version 450 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec4 Color;
uniform sampler2D aTexture;
uniform int textureSample = 1;

void main()
{
    if (textureSample)
    {
        FragColor = texture(aTexture, texCoord) * Color;
    }
    else
    {
        FragColor = Color;
    }
}