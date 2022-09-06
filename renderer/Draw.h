#ifndef _H_DRAW_
#define _H_DRAW_

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class VertexBuffer;
class IndexBuffer;

enum class DrawMode {
	Points,
	LineStrip,
	LineLoop,
	Lines,
	Triangles,
	TriangleStrip,
	TriangleFan
};


void Draw(VertexBuffer& inVertexBuffer, DrawMode mode);

void Draw(IndexBuffer& inIndexBuffer, DrawMode mode);
void Draw(unsigned int vertexCount, DrawMode mode);

void DrawInstanced(IndexBuffer& inIndexBuffer, DrawMode mode, unsigned int instanceCount);
void DrawInstanced(unsigned int vertexCount, DrawMode mode, unsigned int numInstances);

void DrawPoint(glm::vec3, glm::vec3=glm::vec3{}); // point, color
void DrawLine(glm::vec3, glm::vec3, glm::vec3=glm::vec3{}); // point1, point2, color

#endif