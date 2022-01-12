#version 450 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
  
uniform Material material;
uniform Light light;

uniform vec3 viewPos;

uniform vec3 LightColor;
uniform vec3 LightPosition;

uniform sampler2D aTexture;
uniform int hasTexture;

void main()
{

    // Ambient
    vec3 ambient = light.ambient * LightColor * material.ambient;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;

    // Specular
    vec3 viewDirection = normalize(viewPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);


    vec4 colorResult = vec4((ambient + diffuse + specular), 1.0f);


    if (hasTexture == 1)
    {
        FragColor = texture(aTexture, texCoord) * colorResult;
    }
    else
    {
        FragColor = colorResult;
    }
}