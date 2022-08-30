#version 440 core

layout(location=0) in vec3 aPosition;
layout(location=1) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 TexCoord;


void main(void){
	// move normal and vertexpos to world space
	TexCoord = aTexCoord;

	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}