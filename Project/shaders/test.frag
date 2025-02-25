#version 460 core

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};  

uniform Material material;

void main()
{
    vec4 diffuse = texture(material.texture_diffuse1, TexCoords);
    vec4 specular = texture(material.texture_specular1, TexCoords);

    FragColor = diffuse;
}