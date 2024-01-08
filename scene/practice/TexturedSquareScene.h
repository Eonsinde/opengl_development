#pragma once

#include "../../core/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

class TexturedSquareApp : public Hound::Application
{

};

class TexturedSquareLevel : public Hound::Scene
{
public:
	TexturedSquareLevel()
	{
		char title[]{ "Textured Square Scene" };
		strcpy_s(mSceneInfo.title, sizeof(title), title);
		mSceneInfo.mResolution.width = 800;
		mSceneInfo.mResolution.height = 600;
	}

	virtual ~TexturedSquareLevel() {

	}

	virtual void Init() override;
	virtual void LoadScene() override;
	virtual void UnloadScene() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	unsigned int vao, vbo, ebo;
	Shader* mainShader;
};


DECLARE_MAIN(TexturedSquareApp, TexturedSquareLevel)

