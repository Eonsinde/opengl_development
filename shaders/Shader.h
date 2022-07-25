#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>


class Shader
{
	#define U_INT unsigned int
public:
	enum class Shader_Type : int {
		VERTEX=0,
		FRAGMENT=1
	};

private:
	U_INT m_Vertex, m_Fragment;
	U_INT m_Program;

public:
	Shader(const char*, const char*);
	~Shader();

	// made this methods static so they can be used outside the class 
	static U_INT loadAndCompileShader(const char*, const char*); // returns a glProgram with vertex and frag shader attached
	static void checkShaderCompilation(const U_INT&, Shader_Type); // glShader, type
	static void checkProgramCompilation(const U_INT&); // glProgram
	static int getUniformLocation(const U_INT&, const char*); // glProgram, uniform_name

	void use() const { glUseProgram(m_Program); }

	// to send data down the GP
	// usual pattern used here is: uniform name/id, data_to_be_stored_in_uniform
	void setInt(const char*, const int value);
	void setFloat(const char*, const float);

	void setVec2f(const char*, const float, const float);
	void setVec2fv(const char*, const float*);
	void setVec3f(const char*, const float, const float, const float);
	void setVec3fv(const char*, const float*);
	void setVec4f(const char*, const float, const float, const float, const float);
	void setVecf4v(const char*, const float*);

	void setMat3fv(const char*, const float*);
	void setMat4fv(const char*, const float*);
};

