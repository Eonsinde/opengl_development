#include "Draw.h"

#include <glad/glad.h>
#include <iostream>
#include <vector>

#include "./VertexArray.h"
#include "./buffers/IndexBuffer.h"
#include "./buffers/VertexBuffer.h"


static GLenum DrawModeToGLEnum(DrawMode input) {
	if (input == DrawMode::Points) {
		return  GL_POINTS;
	}
	else if (input == DrawMode::LineStrip) {
		return GL_LINE_STRIP;
	}
	else if (input == DrawMode::LineLoop) {
		return  GL_LINE_LOOP;
	}
	else if (input == DrawMode::Lines) {
		return GL_LINES;
	}
	else if (input == DrawMode::Triangles) {
		return GL_TRIANGLES;
	}
	else if (input == DrawMode::TriangleStrip) {
		return GL_TRIANGLE_STRIP;
	}
	else if (input == DrawMode::TriangleFan) {
		return GL_TRIANGLE_FAN;
	}

	std::cout << "DrawModeToGLEnum unreachable code hit\n";
	return 0;
}

void Draw(VertexBuffer& inVertexBuffer, DrawMode mode)
{
	unsigned int handle = inVertexBuffer.GetHandle();
	unsigned int vertexCount = inVertexBuffer.Count();

	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glDrawArrays(DrawModeToGLEnum(mode), 0, vertexCount);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Draw(unsigned int vertexCount, DrawMode mode) {
	glDrawArrays(DrawModeToGLEnum(mode), 0, vertexCount);
}

void DrawInstanced(unsigned int vertexCount, DrawMode mode, unsigned int numInstances) {
	glDrawArraysInstanced(DrawModeToGLEnum(mode), 0, vertexCount, numInstances);
}

void Draw(IndexBuffer& inIndexBuffer, DrawMode mode) {
	unsigned int handle = inIndexBuffer.GetHandle();
	unsigned int numIndices = inIndexBuffer.Count();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glDrawElements(DrawModeToGLEnum(mode), numIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DrawInstanced(IndexBuffer& inIndexBuffer, DrawMode mode, unsigned int instanceCount) {
	unsigned int handle = inIndexBuffer.GetHandle();
	unsigned int numIndices = inIndexBuffer.Count();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	glDrawElementsInstanced(DrawModeToGLEnum(mode), numIndices, GL_UNSIGNED_INT, 0, instanceCount);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// customized functions to render primitives
void DrawPoint(glm::vec3 point, glm::vec3 color)
{
	// the point shader has to be in use here 
	// set vertex attrib at location zero in currently active shader
	glVertexAttrib3fv(0, glm::value_ptr(point));

	// trigger the draw command to render point
	glDrawArrays(GL_POINTS, 0, 1);	
}

void DrawLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 color)
{
	// the line shader has to be in use here
	/*std::cout << "P1: " << "x: " << p1.x << " y: " << p1.y << " z: " << p1.z << '\n';
	std::cout << "P2: " << "x: " << p2.x << " y: " << p2.y << " z: " << p2.z << '\n';*/

 	std::vector<float> points;
	points.reserve(6);
	points = { p1.x, p1.y, p1.z, p2.x, p2.y, p2.z };
	//std::vector<float> points { 0.5f, -0.5f, 0.0f, p2.x, p2.y, p2.z };

	VertexBuffer VBO;
	// create VAO that will be used
	VertexArray VAO;

	// create VBO that will store points used to render line
	VBO.Set(points, VERTEX_ATTRIB::VA_POSITION);

	// register VBO's data with VAO 
	VAO.RegisterBuffer(VBO);
	
	VAO.Bind();
	glDrawArrays(GL_LINES, 0, 2);
	VAO.Unbind();
}

