#include "VertexBuffer.h"

#include <iostream>


VertexBuffer::VertexBuffer() 
	: m_Count{}, m_IsSet{ 0 }, m_NumOfVertexAttribs{} {
	glGenBuffers(1, &m_Handle);
	m_Count = 0;
}

VertexBuffer::~VertexBuffer() 
{
	glDeleteBuffers(1, &m_Handle);
}

void VertexBuffer::Set(float* pArray, unsigned int pNumOfVertexAtribs, unsigned int pLen)
{
	m_Count = pLen;
	m_NumOfVertexAttribs = pNumOfVertexAtribs;
	m_BufferDataType = VertexBufferDataType::FLOAT;

	unsigned int size = sizeof(float);
	/*std::cout << "x:" << pArray[0] << " y:" << pArray[1] << " z:" << pArray[2] << '\n';
	std::cout << "x:" << pArray[3] << " y:" << pArray[4] << " z:" << pArray[5] << '\n';*/

	glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
	glBufferData(GL_ARRAY_BUFFER, size * m_Count, pArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_IsSet = true;
}

void VertexBuffer::Set(std::vector<float>& pVector, unsigned int pNumOfVertexAtribs) {
	/*std::cout << "x:" << pVector.at(0) << " y:" << pVector.at(1) << " z:" << pVector.at(2) << '\n';
	std::cout << "x:" << pVector.at(3) << " y:" << pVector.at(4) << " z:" << pVector.at(5) << '\n';*/
	Set(pVector.data(), pNumOfVertexAtribs, (unsigned int)pVector.size());
}

GLenum convertBufferDataTypeToGLenum(VertexBufferDataType pInstance) {
	switch (pInstance) {
		case VertexBufferDataType::FLOAT:
			return GL_FLOAT;
		case VertexBufferDataType::VERTEX:
			return GL_FLOAT;
	}
}


