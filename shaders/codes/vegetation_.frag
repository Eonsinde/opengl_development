#version 440 core

in vec2 TexCoord;

uniform sampler2D veg_diffuse;

out vec4 fragColor;


void main(void){
	vec4 texelColor = texture(veg_diffuse, TexCoord);

	if (texelColor.a < 0.1)
		discard;
	fragColor = texelColor;
}