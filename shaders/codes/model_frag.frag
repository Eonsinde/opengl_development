#version 440 core

out vec4 FragColor;

in vec2 TexCoords;


struct Material{
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_diffuse4;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
    sampler2D texture_specular3;
    sampler2D texture_specular4;
};


uniform Material uMaterial;


void main()
{    
    FragColor = texture(uMaterial.texture_diffuse1, TexCoords);
}