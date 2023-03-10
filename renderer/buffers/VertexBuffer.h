#ifndef __HOUND_VERTEXBUFFER__
#define __HOUND_VERTEXBUFFER__

#include <vector>
#include <glad/glad.h>
#include "../VertexArray.h"
#include "../../modelLoader/HModel.h"


enum class VertexBufferDataType {
	FLOAT,
	VERTEX,
};

//#define NATIVE_FLOAT float										
//#define CONVERT_VB_DATA_TYPE_TO_NATIVE_TYPE(buffer_data_type)	\
//if (buffer_data_type == VertexBufferDataType::FLOAT)			\
//	NATIVE_FLOAT;												\
//else if (buffer_data_type == VertexBufferDataType::Vertex)		\
//	NATIVE_FLOAT;												\

GLenum convertBufferDataTypeToGLenum(VertexBufferDataType);

class VertexBuffer {
private:
	unsigned int			m_Handle;
	unsigned int			m_Count;
	VERTEX_ATTRIB			m_VertexAttribFormat;

	bool					m_IsSet; // to tell if vertex data has been written to memory
	VertexBufferDataType	m_BufferDataType;

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;

public:
	VertexBuffer();
	~VertexBuffer();

	void					Set(float* pArray, VERTEX_ATTRIB vertexAttribFormat, unsigned int pSize);
	void					Set(std::vector<float>& pVector, VERTEX_ATTRIB vertexAttribFormat);
	void					Set(std::vector<glm::vec3>& pVector, VERTEX_ATTRIB vertexAttribFormat);
	void					Set(std::vector<Hound::HVertex>& pVector, VERTEX_ATTRIB vertexAttribFormat);
	//void Set(std::vector<Vertex>& pVector);

	void					Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_Handle); }
	void					Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	unsigned int			Count()		const { return m_Count; }
	bool					IsSet()		const { return m_IsSet; }
	unsigned int			GetHandle()	const { return m_Handle; }
	VertexBufferDataType	GetBufferDataType() const { return m_BufferDataType; }
	VERTEX_ATTRIB			GetVertexAttribFormat() const { return m_VertexAttribFormat; }
};


#endif