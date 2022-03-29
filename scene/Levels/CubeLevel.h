#pragma once

#include "../../core/Application.h"
#include "../Scene.h"

class CubeLevelApp : public Hound::Application 
{
	
};

class CubeLevel : public Hound::Scene
{
public:
	CubeLevel() {
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

};




