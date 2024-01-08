# OpenGL Development
This is project consists of various graphical scenes rendered in OpenGL

## Quick Setup of Dependencies

Although the dependent libraries for this project reside in the repo, it is advised to manually setup some yourself and replace the corresponding library in the dependencies directory
- Window setup: Make sure to download GLFW and setup it up for your machine using CMAKE to generate a sln file and thereafter, build the library to match your processor's architecture (32bit | 64bit)
- GL functions querying library: This project makes use of GLAD for querying GL functions. Go to [GLAD](https://nextjs.org/):
	- Select the core profile
	- API level can be from version 3.3 upwards
	- Finally, hit generate
- Math library: GLM is used for mathemtical operations
- Image loading: STB is used for loading textures
- Model loading: ASSIMP is used for model loading

## Include & Linking options

This step is not compulsory as the *.vcxproj file should help with these configurations automatically. For convenience sake, it would be included
- The include options can be configured under: project properties > c/c++ > Additional include directories
- The linkng options can be configured under: project properties > linking > Additional libraries directories

## Project structure

| directory | Description |
|---|---|
| **`assets`** | Contains assets such as `images`, `fonts`, and `models` |
| **`core`** | This directories contains the libraries used to core functionalities such as `creating window instance`, `handling keyboard and mouse inputs` |
| **`dependencies`** | As the name implies, it holds libraries required for the successful execution of the project |
| **`ImGUI`** | External library used for UI rendering in scenes |
| **`modelLoader`** | Custom codes for loading OBJ model files |
| **`renderer`** | Contains code files that helps with passing data fown the graphics pipeline |
| **`scene`** | Contains different simulations |
| **`shaders`** | Shader class for loading shaders and shader codes |
| **`textures`** | Texture class for loading textures |

## Creating a scene

Instantiating a scene is a very simple process and can be achieved rapidly by exploring one of the scene classes in the scenes directory. Let's explore the scene > practice > TexturedSquareScene

## Usage

```C++
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
```

All that needs to be done is create an application instance inheritance from the core Application(`This class is responsible for handling window generating and other window related functionalities`) interface.
Next, create a scene instance inheriting from our Scene interface. Finally, used the DECLARE_MAIN(`Declared in the Application.h file, this function is used to invoke the main function`) to instantiate our application and bind the scene to it



