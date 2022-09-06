#include "IndexBuffer.h"
#include <glad/glad.h>



IndexBuffer::IndexBuffer() 
	: m_Count{}, m_IsSet{ 0 } {
	glGenBuffers(1, &m_Handle);
}

IndexBuffer::~IndexBuffer() 
{
	glDeleteBuffers(1, &m_Handle);
}

void IndexBuffer::Set(unsigned int* pArray, unsigned int pLen) 
{
	m_Count = pLen;
	unsigned int size = sizeof(unsigned int);
	m_BufferDataType = IndexBufferDataType::UNSIGNED_INT;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * m_Count, pArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_IsSet = 1;
}

void IndexBuffer::Set(std::vector<unsigned int>& pVector) 
{
	Set(&pVector[0], (unsigned int)pVector.size());
}
