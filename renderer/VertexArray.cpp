#include "VertexArray.h"

#include <iostream>
#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_Handle);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Handle);
}

void VertexArray::SetLayout(VertexBuffer& pVBO)
{
	// numOfVertexAttribs(vertex position, normals, color, texCoord :: 4 in this case),
	switch (pVBO.GetVertexAtrribsCount()) {
		case 1: // position
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), 
								  GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

		case 2: // position, normal
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), 
								  GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
								  GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

		case 3: // position, normal, texCoord
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), 
								  GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), 
								  GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

		case 4: // position, normal, texCoord, colors
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 11 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
			glEnableVertexAttribArray(3);
	}
}

void VertexArray::RegisterBuffer(VertexBuffer& pVBO) 
{
	if (pVBO.IsSet()) { // the buffer data should be set before attempting to register it
		glBindVertexArray(m_Handle);
		
		// bind buffer firstly to register it with VAO
		glBindBuffer(GL_ARRAY_BUFFER, pVBO.GetHandle());
		// tell VAO how to send the buffer's data down the GP
		SetLayout(pVBO);
		
		glBindVertexArray(0);
	}
	else
		std::cerr << "ERROR::VERTEX ARRAY OBJECT::Failed to register unset Vertex Buffer\n";
}

void VertexArray::RegisterBuffer(IndexBuffer& pEBO) 
{
	if (pEBO.IsSet()) { // the buffer data should be set before attempting to register it
		glBindVertexArray(m_Handle);

		// bind buffer firstly to register it with VAO
		glBindBuffer(GL_ARRAY_BUFFER, pEBO.GetHandle());

		glBindVertexArray(0);
	}
	else
		std::cerr << "ERROR::VERTEX ARRAY OBJECT::Failed to register unset Index Buffer\n";
}

