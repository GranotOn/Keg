#version 450 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform vec4 Color;

uniform vec3 LightColor;
uniform float AmbientStrength;
uniform float SpecularStrength;
uniform vec3 LightPosition;

uniform sampler2D aTexture;
uniform int hasTexture;

void main()
{
    int shininess = 64;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(LightPosition - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * LightColor;

    // Specular
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);
    vec3 specular = SpecularStrength * spec * LightColor;

    // Ambient
    vec3 ambient = AmbientStrength * LightColor;

    vec4 colorResult = vec4((ambient + diffuse + specular), 1.0f) * Color;


    if (hasTexture == 1)
    {
        FragColor = texture(aTexture, texCoord) * colorResult;
    }
    else
    {
        FragColor = colorResult;
    }
}