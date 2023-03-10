#pragma once

#define use_imgui
#include "../../core/Application.h"
#include "../Scene.h"
#include "../Camera.h"

#include "../../shaders/Lights/PointLight.h"
#include "../../shaders/Lights/DirectionalLight.h"
#include "../../shaders/Material.h"
#include "../../textures/Texture.h"

#include "../../modelLoader/utils.h"
#include "../../modelLoader/HModel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <future>

class Shader;
class VertexArray;
class VertexBuffer;

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
			mainCamera.MovementSpeed += 0.8f;
		if (key == GLFW_KEY_KP_SUBTRACT)
			mainCamera.MovementSpeed -= 0.2f;
	}


	void onMouseMove(int x, int y) override final
	{
		// update mouse collider
		mMouseCollider.x0 = x; mMouseCollider.y0 = y;
		mMouseCollider.x1 = x + 1; mMouseCollider.y1 = y + 1;

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


		if (hasIntersection(mSceneCollider, mMouseCollider)) {
			mainCamera.ProcessMouseMovement(xoffset, yoffset);
		}
	}

	void onMouseWheel(int yOffset) override final
	{
		if (hasIntersection(mSceneCollider, mMouseCollider)) {
			mainCamera.ProcessMouseScroll(yOffset);
		}
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
		: cubeVAO{}, lightShader{ nullptr }, basicShader{ nullptr }, mCubeTexture{ nullptr } {
		char title[]{ "Mesh Loading Scene" };
		strcpy_s(mSceneInfo.title, sizeof(title), "Mesh Loading Scene");
		mSceneInfo.mResolution.width = 1920;
		mSceneInfo.mResolution.height = 1080;
	}

	virtual ~MeshLoadingLevel() {

	}

	virtual void Init() override;
	virtual void LoadScene() override;
	virtual void UnloadScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	VertexArray* cubeVAO;
	VertexBuffer* cubeVBO;
	VertexArray* quadVAO;
	VertexBuffer* quadVBO;

	Shader* lightShader;
	Shader* basicShader;

	// models
	Hound::HModel cubeModel;
	std::future<bool> success;

	// Lights
	Hound::DirectionalLight mDirectionalLight;
	float lightRotationRad = 10.0f; // light rotation radius

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