#include "TriangleLevel.h"
#include "../../shaders/Shader.h"

#include "../../core/Input.h"

void TriangleLevel::Init()
{
	float vertices[]{
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

	// create VAO and bind buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	mShader = new Shader("./shaders/codes/basic.vert", "./shaders/codes/basic.frag");
}

void TriangleLevel::LoadScene()
{

}

void TriangleLevel::UnloadScene()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void TriangleLevel::Update(float deltaTime)
{
	if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
		std::cout << "Adding to movement speed\n";
	if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
		std::cout << "Removing from movement speed\n";
}

void TriangleLevel::Draw()
{
	mShader->use();

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 0.24f, 0.45f, 1.0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

