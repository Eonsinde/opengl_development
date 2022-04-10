#pragma once

#include "../../core/Application.h"
#include "../Scene.h"
#include "../Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

static Hound::Camera mainCamera;

class BasicLightingApp : public Hound::Application
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
			mainCamera.MovementSpeed += 0.2f;
		if (key == GLFW_KEY_KP_SUBTRACT)
			mainCamera.MovementSpeed -= 0.2f;
	}

	virtual void onMouseMove(int x, int y)
	{
		float xpos = static_cast<float>(x);
		float ypos = static_cast<float>(y);

		if (firstMouse)
		{
			// update with current mouse position
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		mainCamera.ProcessMouseMovement(xoffset, yoffset);
	}

protected:
	float lastX = (float)mInfo.windowWidth / 2.0f;
	float lastY = (float)mInfo.windowHeight / 2.0f;
	bool firstMouse = true;
};


class BasicLightingLevel : public Hound::Scene
{
public:
	BasicLightingLevel()
		: cubeVAO{}, lightVAO{}, VBO{}, lightShader{ nullptr }, cubeShader{ nullptr } {
		char title[]{ "Cube Level" };
		strcpy_s(mSceneInfo.title, sizeof(title), "Cube Level");
		mSceneInfo.width = 800;
		mSceneInfo.height = 600;
	}

	virtual ~BasicLightingLevel() {

	}

	virtual void Init() override;
	virtual void LoadScene() override;
	virtual void UnloadScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	unsigned int cubeVAO, lightVAO, VBO;
	Shader* lightShader;
	Shader* cubeShader;

	// matrices
	glm::mat4 idMat{ 1.0f }; // identity matrix
	glm::mat4 model, view, projection;
};


DECLARE_MAIN(BasicLightingApp, BasicLightingLevel)




