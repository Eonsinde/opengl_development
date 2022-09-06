#pragma once

#include "../Shader.h"



class LineShader : public Shader
{
private:
	// Source code for vertex shader
	const GLchar* m_vertex_shader_source =
		"#version 450 core \n"
		" \n"
		"layout(location=0) in vec3 aPosition; \n"
		" \n"
		"void main(void) \n"
		"{ \n"
		" gl_Position = vec4(aPosition, 1.0); \n"
		"} \n";

	// Source code for fragment shader
	const GLchar* m_fragment_shader_source =
		"#version 450 core \n"
		" \n"
		"uniform vec3 uPixelColor; \n"
		" \n"
		"out vec4 FragColor; \n"
		" \n"
		"void main(void) \n"
		"{ \n"
		" FragColor = vec4(uPixelColor, 1.0); \n"
		"} \n";

private: 
	LineShader(const char*, const char*);

public:
	LineShader();
	~LineShader() = default;
};

