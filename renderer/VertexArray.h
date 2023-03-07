#pragma once

#include <vector>
#include <glad/glad.h>


class VertexBuffer;
class IndexBuffer;


enum class VERTEX_ATTRIB
{ 
	VA_POSITION, 
	VA_NORMAL,
	VA_TEXCOORD,
	VA_POS_NORM,
	VA_POS_TEXCOORD,
	VA_POS_NORM_TEXCOORD,
	VA_POS_NORM_TEXCOORD_COLOR,
	VA_POS_TEXCOORD_NORMAL,
	VA_POS_TEXCOORD_NORMAL_COLOR
};


class VertexArray {
private:
	unsigned int m_Handle;

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;

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

