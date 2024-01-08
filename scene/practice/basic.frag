#version 440 core

uniform vec3 uPixelColor;

out vec4 fragColor;

void main(void){
	fragColor = vec4(uPixelColor, 1.0);
}