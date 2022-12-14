#version 440 core


in vec2 TexCoord;

uniform sampler2D texture_diffuse;

float near = 0.1;
float far = 100.0;

out vec4 fragColor;


float LinearizeDepth(float depth){
	float z = depth * 2.0 - 1.0; // back to NDC (from [0, 1] to [-1, 1])
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main(void){
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	fragColor = vec4(vec3(depth), 1.0);
}