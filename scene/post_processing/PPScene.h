#pragma once

#define use_imgui
#include "../../core/Application.h"
#include "../Scene.h"
#include "../Camera.h"

#include "../../textures/Texture.h"
#include "../../shaders/Material.h"

#include "../../renderer/VertexArray.h"
#include "../../renderer/buffers/VertexBuffer.h"

#include "../../../modelLoader/Model.h"
#include "../../modelLoader/utils.h"

#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

static Hound::Camera mainCamera;

class MyApp : public Hound::Application
{
public:
	MyApp() {
		// enable v-sync with app info component
		mInfo.flags.vsync = 1;
		mInfo.flags.cursor = 0;
	}

protected:
	void onKey(int key, int action) override final
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

	void renderUI() override final
	{
#ifdef use_imgui

#endif
	}

protected:
	float lastX = (float)mInfo.windowWidth / 2.0f;
	float lastY = (float)mInfo.windowHeight / 2.0f;
	bool firstMouse = true;

	// to adjust color buffer
#ifdef use_imgui
	ImVec4 mClearColor = ImVec4(0.0784f, 0.0784f, 0.0784f, 1.0);
#endif
};


class PPScene : public Hound::Scene
{
public:
	PPScene()
		: mainShader{ nullptr }, fbQuadShader{ nullptr }, mCubeTexture{ nullptr },
		//cubeVAO{}, planeVAO{}, glassVAO{}, cubeVBO{}, planeVBO{}, glassVBO{},
		mPlaneTexture{ nullptr }
	{
		char title[]{ "Post Processing Scene" };
		strcpy_s(mSceneInfo.title, sizeof(title), title);
		mSceneInfo.mResolution.width = 1920;
		mSceneInfo.mResolution.height = 1080;
	}

	virtual ~PPScene() {

	}

	virtual void Init() override;
	virtual void LoadScene() override;
	virtual void UnloadScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	unsigned int cubeVAO, planeVAO, quadVAO;
	unsigned int cubeVBO, planeVBO, quadVBO;
	unsigned int frameBuffer;
	unsigned int textureColorBuffer; // framebuffer attachment 
	unsigned int rbo; // render buffer object

	Shader* mainShader;
	Shader* fbQuadShader; // frame buffer quad shader

	// materials and textures
	Hound::Material mCubeMaterial;
	Hound::Material mPlaneMaterial;

	Hound::Texture* mCubeTexture;
	Hound::Texture* mPlaneTexture;

	// matrices
	glm::mat4 idMat{ 1.0f }; // identity matrix
	glm::mat4 model, view, projection;

	// positions all containers
	glm::vec3 mCubePositions[2] = {
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
	};
};


DECLARE_MAIN(MyApp, PPScene)
