#ifndef __HOUND_INDEXBUFFER__
#define __HOUND_INDEXBUFFER__

#include <vector>
#include <glad/glad.h>


enum class IndexBufferDataType {
	UNSIGNED_INT,
	UNSIGNED_BYTE,
};


class IndexBuffer {
private:
	unsigned int			m_Handle;
	unsigned int			m_Count;
	bool					m_IsSet;
	IndexBufferDataType		m_BufferDataType;

	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer& operator=(const IndexBuffer& other) = delete;

public:
	IndexBuffer();
	~IndexBuffer();

	void					Set(unsigned int* pArray, unsigned int pLen);
	void					Set(std::vector<unsigned int>& pVector);

	void					Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle); }
	void					Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);; }

	unsigned int			Count() const { return m_Count; }
	bool					IsSet()		const { return m_IsSet; };
	unsigned int			GetHandle() const { return m_Handle; }
	IndexBufferDataType		GetBufferDataType() const { return m_BufferDataType; }
};


#endif