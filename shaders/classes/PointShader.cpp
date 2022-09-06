#include "PointShader.h"



PointShader::PointShader()
{
	m_Program = Shader::loadAndCompileShader(m_vertex_shader_source, m_fragment_shader_source);
}

