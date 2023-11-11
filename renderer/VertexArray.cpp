#include "VertexArray.h"

#include <iostream>
#include "buffers/VertexBuffer.h"
#include "buffers/IndexBuffer.h"


VertexArray::VertexArray() 
	: m_Handle{ } {
	glGenVertexArrays(1, &m_Handle);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Handle);
}

void VertexArray::SetLayout(VertexBuffer& pVBO)
{
	// numOfVertexAttribs (vertex position, normals, color, texCoord :: 4 in this case),
	switch (pVBO.GetVertexAttribFormat()) {
		case VERTEX_ATTRIB::VA_POSITION: // position
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			return;

		case VERTEX_ATTRIB::VA_NORMAL:
			glVertexAttribPointer(1, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			return;

		case VERTEX_ATTRIB::VA_TEXCOORD:
			glVertexAttribPointer(2, 2, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(0);
			return;

		case VERTEX_ATTRIB::VA_POS_NORM: // position, normal
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), 
								  GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
								  GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			return;

		case VERTEX_ATTRIB::VA_POS_TEXCOORD:
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			return;

		// these formats are used with my practice convention
		case VERTEX_ATTRIB::VA_POS_NORM_TEXCOORD: // position, normal, texCoord
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
			return;

		case VERTEX_ATTRIB::VA_POS_NORM_TEXCOORD_COLOR: // position, normal, texCoord, color
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
			glEnableVertexAttribArray(2);
			return;

		// these formats here are used with actual model files
		case VERTEX_ATTRIB::VA_POS_TEXCOORD_NORMAL: // position, texCoord, normal
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			return;

		case VERTEX_ATTRIB::VA_POS_TEXCOORD_NORMAL_COLOR: // position, texCoord, normal, color
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), // position
				GL_FALSE, 11 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), // normal
				GL_FALSE, 11 * sizeof(float), (void*)(5 * sizeof(float)));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 2, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), // texCoord
				GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(3, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()), // color
				GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
			glEnableVertexAttribArray(3);
			return;

		default: // assume it's just a position
			glVertexAttribPointer(0, 3, convertBufferDataTypeToGLenum(pVBO.GetBufferDataType()),
				GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			return;
	}
}

void VertexArray::RegisterBuffer(VertexBuffer& pVBO) 
{
	if (pVBO.IsSet()) { // the buffer data should be set before attempting to register it
		glBindVertexArray(m_Handle);
		
		// bind buffer firstly to register it with VAO
		glBindBuffer(GL_ARRAY_BUFFER, pVBO.GetHandle());
		// tell VAO how to send the buffer's data down to our shaders/programmable pipeline
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

