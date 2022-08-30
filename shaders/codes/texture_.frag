#version 440 core


in vec2 TexCoord;

uniform sampler2D texture_diffuse;

out vec4 fragColor;


void main(void){
//	fragColor = vec4(vec3(texture(texture_diffuse, TexCoord)), 1.0);
	fragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}