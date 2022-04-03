#pragma once
#include "../../core/Application.h"
#include "../Scene.h"


class TriangleLevelApp : public Hound::Application
{

};

class Shader;

class TriangleLevel : public Hound::Scene
{
public:
	TriangleLevel()
		: VAO{}, VBO{}, mShader{ nullptr } {
		char title[]{ "Triangle Level" };
		strcpy_s(mSceneInfo.title, sizeof(title), "Triangle Level");
		mSceneInfo.width = 800;
		mSceneInfo.height = 600;
	}

	virtual ~TriangleLevel() {

	}

	virtual void Init() override;
	virtual void LoadScene() override;
	virtual void UnloadScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	unsigned int VAO, VBO;
	Shader* mShader;
};


//DECLARE_MAIN(TriangleLevelApp, TriangleLevel)