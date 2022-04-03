#pragma once

#include "../../core/Application.h"
#include "../Scene.h"
#include "../Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

Hound::Camera mainCamera;

class CubeLevelApp : public Hound::Application 
{
	virtual void onKey(int key, int action)
	{
		if (key == GLFW_KEY_W)
			mainCamera.ProcessKeyboard(FORWARD, Application::GetDeltaTime());
		if (key == GLFW_KEY_S)
			mainCamera.ProcessKeyboard(BACKWARD, Application::GetDeltaTime());
		if (key == GLFW_KEY_A)
			mainCamera.ProcessKeyboard(LEFT, Application::GetDeltaTime());
		if (key == GLFW_KEY_D)
			mainCamera.ProcessKeyboard(RIGHT, Application::GetDeltaTime());

		if (key == GLFW_KEY_KP_ADD)
			mainCamera.MovementSpeed += 0.1f;
		if (key == GLFW_KEY_KP_SUBTRACT)
			mainCamera.MovementSpeed -= 0.1f;
	}

	virtual void onMouseMove(int x, int y)
	{

	}
};


class CubeLevel : public Hound::Scene
{
public:
	CubeLevel()
		: VAO{}, VBO{}, mShader{nullptr} {
		char title[]{ "Cube Level" };
		strcpy_s(mSceneInfo.title, sizeof(title), "Cube Level");
		mSceneInfo.width = 800;
		mSceneInfo.height = 600;
	}

	virtual ~CubeLevel() {

	}

	virtual void Init() override;
	virtual void LoadScene() override;
	virtual void UnloadScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	unsigned int VAO, VBO;
	Shader* mShader;

	// matrices
	glm::mat4 idMat{ 1.0f }; // identity matrix
	glm::mat4 model, view, projection;
};


DECLARE_MAIN(CubeLevelApp, CubeLevel)




