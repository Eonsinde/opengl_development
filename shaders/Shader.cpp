#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << '\n';
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // create vertex shader
    m_Vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_Vertex, 1, &vShaderCode, NULL);
    glCompileShader(m_Vertex);
    checkShaderCompilation(m_Vertex, Shader_Type::VERTEX);

    // create fragment shader
    m_Fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_Fragment, 1, &fShaderCode, NULL);
    glCompileShader(m_Fragment);
    checkShaderCompilation(m_Fragment, Shader_Type::FRAGMENT);

    // create program and link shaders
    m_Program = glCreateProgram();
    glAttachShader(m_Program, m_Vertex);
    glAttachShader(m_Program, m_Fragment);
    glLinkProgram(m_Program);
    checkProgramCompilation(m_Program);

    // cleanup: delete shaders
    glDeleteShader(m_Vertex);
    glDeleteShader(m_Fragment);
}

Shader::~Shader()
{
}

U_INT Shader::loadAndCompileShader(const char*, const char*)
{
	return U_INT();
}

void Shader::checkShaderCompilation(U_INT pShader, Shader_Type pShaderType)
{
    GLint success;
    GLchar infoLog[1024];

    switch (pShaderType) {
        case Shader_Type::VERTEX:
            glGetShaderiv(pShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(pShader, 1024, NULL, infoLog);
                std::cout << "ERR::SHADER::VERTEX_SHADER_FAILED_TO_COMPILE" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
            break;
        case Shader_Type::FRAGMENT:
            glGetShaderiv(pShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(pShader, 1024, NULL, infoLog);
                std::cout << "ERR::SHADER::FRAGMENT_SHADER_FAILED_TO_COMPILE" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
            break;
    }
}

void Shader::checkProgramCompilation(U_INT pProgram)
{
    GLint success;
    GLchar infoLog[1024];

    glGetProgramiv(pProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(pProgram, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << pProgram << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

int Shader::getUniformLocation(U_INT pProgram, const char* pName)
{
	int loc = glGetUniformLocation(pProgram, pName);
	if (loc == -1)
		std::cerr << "ERR::UNIFORM_" << pName << "_NOT_FOUND\n";
	return loc;
}

void Shader::setInt(const char* name, const int value)
{
	glUniform1i(getUniformLocation(m_Program, name), value);
}

void Shader::setFloat(const char* name, const float value)
{
	glUniform1f(getUniformLocation(m_Program, name), value);
}

void Shader::setVec2f(const char* name, const float v0, const float v1)
{
	glUniform2f(getUniformLocation(m_Program, name), v0, v1);
}

void Shader::setVec2fv(const char* name, const float* data)
{
	glUniform2fv(getUniformLocation(m_Program, name), 1, data);
}

void Shader::setVec3f(const char* name, const float v0, const float v1, const float v2)
{
	glUniform3f(getUniformLocation(m_Program, name), v0, v1, v2);
}

void Shader::setVec3fv(const char* name, const float* data)
{
	glUniform3fv(getUniformLocation(m_Program, name), 1, data);
}

void Shader::setVec4f(const char* name, const float v0, const float v1, const float v2, const float v3)
{
	glUniform4f(getUniformLocation(m_Program, name), v0, v1, v2, v3);
}

void Shader::setVecf4v(const char* name, const float* data)
{
	glUniform4fv(getUniformLocation(m_Program, name), 1, data);
}

void Shader::setMat3fv(const char* name, const float* data)
{
	glUniformMatrix3fv(getUniformLocation(m_Program, name), 1, false, data);
}

void Shader::setMat4fv(const char* name, const float* data)
{
	glUniformMatrix4fv(getUniformLocation(m_Program, name), 1, false, data);
}
