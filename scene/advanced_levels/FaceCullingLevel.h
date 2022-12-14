#pragma once

//#define use_imgui
#include "../../core/Application.h"
#include "../Scene.h"
#include "../Camera.h"

#include "../../textures/Texture.h"
#include "../../shaders/Material.h"

#include "../../renderer/VertexArray.h"
#include "../../renderer/buffers/VertexBuffer.h"

#include "../../../modelLoader/Model.h"

#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

static Hound::Camera mainCamera;

class FaceCullingApp : public Hound::Application
{
public:
	FaceCullingApp() {
		// enable v-sync with app info component
		mInfo.flags.vsync = 1;
		mInfo.flags.cursor = 0;
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
#ifdef use_imgui
		ImGui::ShowDemoWindow((bool*)1);

		// create UI to clear color buffer
		ImGui::Begin("Edit Clear Color"); // Create a window called "Hello, world!" and append into it.
		ImGui::ColorEdit3("Clear Color", (float*)&mClearColor); // Edit 3 floats representing a color
		ImGui::End();

		/*ImGui::Begin("ImGui Stats");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();*/

		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, 1.0);
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


class FaceCullingLevel : public Hound::Scene
{
public:
	FaceCullingLevel()
		:  mainShader{ nullptr }, glassShader{ nullptr }, mCubeTexture{ nullptr },
		//cubeVAO{}, planeVAO{}, glassVAO{}, cubeVBO{}, planeVBO{}, glassVBO{},
		mPlaneTexture{ nullptr }, mGlassTexture{ nullptr } 
	{
		char title[]{ "Face Culling Scene" };
		strcpy_s(mSceneInfo.title, sizeof(title), title);
		mSceneInfo.width = 800;
		mSceneInfo.height = 600;
	}

	virtual ~FaceCullingLevel() {

	}

	virtual void Init() override;
	virtual void LoadScene() override;
	virtual void UnloadScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	unsigned int cubeVAO, planeVAO, glassVAO;
	unsigned int cubeVBO, planeVBO, glassVBO;

	Shader* mainShader;
	Shader* glassShader;

	// materials and textures
	Hound::Material mCubeMaterial;
	Hound::Material mPlaneMaterial;

	Hound::Texture* mCubeTexture;
	Hound::Texture* mPlaneTexture;
	Hound::Texture* mGlassTexture;

	// matrices
	glm::mat4 idMat{ 1.0f }; // identity matrix
	glm::mat4 model, view, projection;

	// positions all containers
	glm::vec3 mCubePositions[10] = {
		glm::vec3(-1.0f, 0.0f, -1.0f),
		glm::vec3(2.0f, 0.0f, 0.0f),
	};

	std::vector<glm::vec3> windowPositions{
		glm::vec3(-1.5f, 0.0f, -0.48f),
		glm::vec3(1.5f, 0.0f, 0.51f),
		glm::vec3(0.0f, 0.0f, 0.7f),
		glm::vec3(-0.3f, 0.0f, -2.3f),
		glm::vec3(0.5f, 0.0f, -0.6f)
	};
	std::map<float, glm::vec3> sorted;
};


DECLARE_MAIN(FaceCullingApp, FaceCullingLevel)



