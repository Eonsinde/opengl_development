#include "TexturedSquareScene.h"

#include "../../shaders/Shader.h"

void TexturedSquareLevel::Init()
{
	float vertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
	};
	unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	// generate VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create buffer to store vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// tell vao how to read data from vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// create shader
	mainShader = new Shader("./scene/practice/basic.vert", "./scene/practice/basic.frag");
}

void TexturedSquareLevel::LoadScene()
{
}

void TexturedSquareLevel::UnloadScene()
{
	glBindVertexArray(0);

	delete mainShader;

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

void TexturedSquareLevel::Update(float deltaTime)
{
}

void TexturedSquareLevel::Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mainShader->use();
	mainShader->setVec3fv("uPixelColor", glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.0f)));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
