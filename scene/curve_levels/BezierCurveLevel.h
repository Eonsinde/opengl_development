#pragma once

//#define use_imgui
#include "../../core/Application.h"
#include "../Scene.h"

#include "../../math/curves/Bezier.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader;
class PointShader;
class LineShader;


class BezierCurveApp final : public Hound::Application
{
public:
	BezierCurveApp() {
		// enable v-sync with app info component
		mInfo.flags.vsync = 1;
		mInfo.flags.cursor = 0;
	}

protected:
	void onKey(int key, int action) override
	{
		
	}

	void onMouseMove(int x, int y) override
	{
		
	}

	void onMouseWheel(int yOffset) override
	{
		
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

	// to adjust color buffer
#ifdef use_imgui
	ImVec4 mClearColor = ImVec4(0.0784f, 0.0784f, 0.0784f, 1.0);
#endif
};


class BezierCurveLevel final : public Hound::Scene
{
public:
	BezierCurveLevel()
		: VAO{}, pointShader1{ nullptr }, lineShader1{ nullptr } {
		char title[]{ "Bezier Curve Scene" };
		strcpy_s(mSceneInfo.title, sizeof(title), title);
		mSceneInfo.width = 800;
		mSceneInfo.height = 600;
	}

	virtual ~BezierCurveLevel() {

	}

	virtual void Init() override;
	virtual void LoadScene() override;
	virtual void UnloadScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	unsigned int VAO;

	PointShader* pointShader1;
	LineShader* lineShader1;

	// scene's objects
	Bezier<glm::vec3> bezierCurve1;

	// colors to use
	glm::vec3 red =		 { 1.0f, 0.0f, 0.0f };
	glm::vec3 green	=    { 0.0f, 1.0f, 0.0f };
	glm::vec3 blue =	 { 0.0f, 0.0f, 1.0f };
	glm::vec3 yellow =   { 1.0f, 1.0f, 0.0f };
	glm::vec3 magenta =  { 1.0f, 0.0f, 1.0f };
};


//DECLARE_MAIN(BezierCurveApp, BezierCurveLevel)




