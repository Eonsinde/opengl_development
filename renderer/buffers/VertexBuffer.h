#ifndef __HOUND_VERTEXBUFFER__
#define __HOUND_VERTEXBUFFER__

#include <vector>
#include <glad/glad.h>




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
	unsigned int			m_NumOfVertexAttribs;
	bool					m_IsSet; // to tell if vertex data has been written to memory
	VertexBufferDataType	m_BufferDataType;

	VertexBuffer(const VertexBuffer& other);
	VertexBuffer& operator=(const VertexBuffer& other);

public:
	VertexBuffer();
	~VertexBuffer();

	void					Set(float* pArray, unsigned int pNumOfVertexAttribs, unsigned int pLen);
	void					Set(std::vector<float>& pVector, unsigned int pNumOfVertexAttribs);
	//void Set(std::vector<Vertex>& pVector);

	void					Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_Handle); }
	void					Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	unsigned int			Count()		const { return m_Count; };
	bool					IsSet()		const { return m_IsSet; };
	unsigned int			GetHandle()	const { return m_Handle; };
	VertexBufferDataType	GetBufferDataType() const { return m_BufferDataType; }
	unsigned int			GetVertexAtrribsCount() const { return m_NumOfVertexAttribs; };
};


#endif