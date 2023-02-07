#version 440 core

in vec2 TexCoord;
uniform sampler2D screenTexture;

out vec4 FragColor;

// some custom offset
const float offset = 1.0 / 300.0;

void main()
{
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset), // top-left
		vec2( 0.0f, offset), // top-center
		vec2( offset, offset), // top-right
		vec2(-offset, 0.0f), // center-left
		vec2( 0.0f, 0.0f), // center-center
		vec2( offset, 0.0f), // center-right
		vec2(-offset, -offset), // bottom-left
		vec2( 0.0f, -offset), // bottom-center
		vec2( offset, -offset) // bottom-right
	);

	// sharpening kernel
	float sharpenKernel[9] = float[](
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1
	);

	float edgeOutlineKernel[9] = float[](
		1, 1, 1,
		1, -8, 1,
		1, 1, 1
	);

	float blurKernel[9] = float[](
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16
	);
	
	
	// this logic is to sample texel around the current fragment
	// this is done using the offset define above
	// basically, sample texels around the current fragment 
	// and store them in the sampleTexels array
	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(screenTexture, TexCoord.st + offsets[i]));
	}
	
	// have the kernel affect each sampled texel in the sampleTexels array
	// i.e sampleTex[0] * kernel[0] and so on
	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++)
		col += sampleTex[i] * edgeOutlineKernel[i];

	FragColor = vec4(col, 1.0);
}