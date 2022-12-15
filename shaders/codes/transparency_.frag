#version 440 core

in vec2 TexCoord;

uniform sampler2D glass_diffuse;

out vec4 fragColor;


void main(void){
	vec4 texelColor = texture(glass_diffuse, TexCoord);
	fragColor = texelColor;
}