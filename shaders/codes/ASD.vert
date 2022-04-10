#version 440 core

layout(location=0) in vec3 aPosition;
layout(location=1) in vec3 aTexCoord;
layout(location=2) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 FragPos;
out vec3 TexCoord;
out vec3 Normal;


void main(void){
	FragPos = vec3(uModel * vec4(aPosition, 1.0));
	Normal = vec3(transpose(inverse(uModel)) * vec4(aNormal, 1.0));
	Normal = normalize(Normal);

	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}