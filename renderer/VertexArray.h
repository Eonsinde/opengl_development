#pragma once


#include <vector>
#include <glad/glad.h>


class VertexBuffer;
class IndexBuffer;


class VertexArray {
private:
	unsigned int m_Handle;

	VertexArray(const VertexArray& other);
	VertexArray& operator=(const VertexArray& other);

	void SetLayout(VertexBuffer&);

public:
	VertexArray();
	~VertexArray();

	void			RegisterBuffer(VertexBuffer&);
	void			RegisterBuffer(IndexBuffer&);

	void			Bind() const { glBindVertexArray(m_Handle); }
	void			Unbind() const { glBindVertexArray(0); }

	unsigned int	GetHandle() const { return m_Handle; };
};

