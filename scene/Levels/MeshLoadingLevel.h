#pragma once

#include "../../core/Application.h"
#include "../Scene.h"
#include "../Camera.h"

#include "../../shaders/Lights/PointLight.h"
#include "../../shaders/Lights/DirectionalLight.h"
#include "../../shaders/Material.h"
#include "../../textures/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

static Hound::Camera mainCamera;

class MeshLoadingApp : public Hound::Application
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


class MeshLoadingLevel : public Hound::Scene
{
public:
	MeshLoadingLevel()
		: cubeVAO{}, lightVAO{}, VBO{}, lightShader{ nullptr }, cubeShader{ nullptr }, mCubeTexture{ nullptr } {
		char title[]{ "Mesh Loading Level" };
		strcpy_s(mSceneInfo.title, sizeof(title), "Mesh Loading Level");
		mSceneInfo.width = 800;
		mSceneInfo.height = 600;
	}

	virtual ~MeshLoadingLevel() {

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

	// Lights
	Hound::DirectionalLight mDirectionalLight;
	float lightRotationRad = 10.0f; // ligth rotation radius

	// materials and textures
	Hound::Material mCubeMaterial;
	Hound::Texture* mCubeTexture;
	Hound::Texture* mSpecularMapTexture;

	// matrices
	glm::mat4 idMat{ 1.0f }; // identity matrix
	glm::mat4 model, view, projection;

	// positions all containers
	glm::vec3 mCubePositions[10] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
};


DECLARE_MAIN(MeshLoadingApp, MeshLoadingLevel)