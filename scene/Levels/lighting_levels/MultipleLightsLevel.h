#pragma once


class MultipleLights
{
};


#pragma once

#include "../../core/Application.h"
#include "../../Scene.h"
#include "../../Camera.h"

#include "../../shaders/Lights/PointLight.h"
#include "../../shaders/Lights/SpotLight.h"
#include "../../shaders/Material.h"
#include "../../textures/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

static Hound::Camera mainCamera;

class MultipleLightsApp : public Hound::Application
{
public:
	MultipleLightsApp() {
		// enable v-sync with app info component
		mInfo.flags.vsync = 1;
		mInfo.flags.cursor = 1;
	}

protected:
	void onKey(int key, int action) override
	{
		// camera controls with keyboard
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

	void onMouseMove(int x, int y) override
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

	void onMouseWheel(int yOffset) override
	{
		mainCamera.ProcessMouseScroll(yOffset);
	}

	void renderUI() override {
		ImGui::ShowDemoWindow((bool*)1);

		// create UI to clear color buffer
		ImGui::Begin("Edit Clear Color"); // Create a window called "Hello, world!" and append into it.
		ImGui::ColorEdit3("Clear Color", (float*)&mClearColor); // Edit 3 floats representing a color
		ImGui::End();

		ImGui::Begin("ImGui Stats");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, 1.0);
	}

protected:
	float lastX = (float)mInfo.windowWidth / 2.0f;
	float lastY = (float)mInfo.windowHeight / 2.0f;
	bool firstMouse = true;

	// to adjust color buffer
	ImVec4 mClearColor = ImVec4(0.0784f, 0.0784f, 0.0784f, 1.0);
};


class MultipleLightsLevel : public Hound::Scene
{
public:
	MultipleLightsLevel()
		: cubeVAO{}, lightVAO{}, VBO{}, lightShader{ nullptr }, cubeShader{ nullptr }, mCubeTexture{ nullptr } {
		char title[]{ "Multiple Lights Scene" };
		strcpy_s(mSceneInfo.title, sizeof(title), title);
		mSceneInfo.width = 800;
		mSceneInfo.height = 600;
	}

	virtual ~MultipleLightsLevel() {

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
	Hound::SpotLight mSpotLight;
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


DECLARE_MAIN(MultipleLightsApp, MultipleLightsLevel)

