#pragma once

#include "../../core/Application.h"
#include "../Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

class CubeLevelApp : public Hound::Application 
{
	
};


class CubeLevel : public Hound::Scene
{
public:
	CubeLevel()
		: VAO{}, VBO{}, mShader{nullptr} {
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
	unsigned int VAO, VBO;
	Shader* mShader;

	// matrices
	glm::mat4 idMat{ 1.0f }; // identity matrix
	glm::mat4 model, view, projection;
};


DECLARE_MAIN(CubeLevelApp, CubeLevel)




