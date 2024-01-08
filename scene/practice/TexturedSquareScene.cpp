#include "TexturedSquareScene.h"

#include "../../shaders/Shader.h"

void TexturedSquareLevel::Init()
{
	float vertices[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
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
	glDeleteVertexArrays(1, &vao);
}

void TexturedSquareLevel::Update(float deltaTime)
{
}

void TexturedSquareLevel::Draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mainShader->use();
	mainShader->setVec3fv("uPixelColor", glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.0f)));

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
