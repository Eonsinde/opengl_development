#version 440 core

layout(location=0) in vec3 position;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main(void){
	gl_Position = uProjection * uView * uModel * vec4(position, 1.0);
}