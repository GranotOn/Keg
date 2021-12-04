#version 450 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec4 Color;
uniform vec3 LightColor;
uniform sampler2D aTexture;
uniform int hasTexture;

void main()
{
    if (hasTexture == 1)
    {
        FragColor = texture(aTexture, texCoord) * (Color * vec4(LightColor, 1.0f));
    }
    else
    {
        FragColor = (Color * vec4(LightColor, 1.0f));
    }
}