#include "VertexBuffer.h"

#include <iostream>


VertexBuffer::VertexBuffer() 
	: m_Handle{ }, m_Count{ }, m_IsSet{ } {
	glGenBuffers(1, &m_Handle);
}

VertexBuffer::~VertexBuffer() 
{
	glDeleteBuffers(1, &m_Handle);
}

void VertexBuffer::Set(float* pArray, VERTEX_ATTRIB vertexAttribFormat, unsigned int pSize)
{
	m_Count = pSize/sizeof(float);
	m_VertexAttribFormat = vertexAttribFormat;
	m_BufferDataType = VertexBufferDataType::FLOAT;

	glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
	glBufferData(GL_ARRAY_BUFFER, pSize, pArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_IsSet = true;
}

void VertexBuffer::Set(std::vector<float>& pVector, VERTEX_ATTRIB vertexAttribFormat) {
	Set(pVector.data(), vertexAttribFormat, sizeof(pVector.data()));
}

GLenum convertBufferDataTypeToGLenum(VertexBufferDataType pInstance) {
	switch (pInstance) {
		case VertexBufferDataType::FLOAT:
		case VertexBufferDataType::VERTEX:
		default:
			return GL_FLOAT;
	}
}


