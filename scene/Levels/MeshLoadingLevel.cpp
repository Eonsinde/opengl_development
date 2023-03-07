#include "MeshLoadingLevel.h"

#include "../../shaders/Shader.h"
#include "../../core/Input.h"

#include "../scene_management/Plane.h"
#include "../../modelLoader/OBJLoader.h"
#include "../../renderer/VertexArray.h"
#include "../../renderer/buffers/VertexBuffer.h"


void MeshLoadingLevel::Init()
{
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    //Hound::loadObjMesh("./input_test_file.txt");
    testVAO = new VertexArray();
    testVBO = new VertexBuffer();

    testVBO->Set(vertices, VERTEX_ATTRIB::VA_POS_NORM_TEXCOORD, sizeof(vertices));
    testVAO->RegisterBuffer(*testVBO);
}

void MeshLoadingLevel::LoadScene()
{
    cubeShader = new Shader("./shaders/codes/basic.vert", "./shaders/codes/basic.frag");
    lightShader = new Shader("./shaders/codes/ADS.vert", "./shaders/codes/dirlight_ADS.frag");

    mCubeTexture = new Hound::Texture("./assets/textures/wooden_metallic_container.png");
    mSpecularMapTexture = new Hound::Texture("./assets/textures/wooden_metallic_specular_container.png");

    mDirectionalLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
    mDirectionalLight.ambient = glm::vec3(0.1f);
    mDirectionalLight.diffuse = glm::vec3(1.0f);
    mDirectionalLight.specular = glm::vec3(0.5f);

    mCubeMaterial.specExp = 32.0f;
}

void MeshLoadingLevel::UnloadScene()
{
    if (lightShader)
        delete lightShader;
    if (cubeShader)
        delete cubeShader;
    if (mCubeTexture)
        delete mCubeTexture;

    if (testVAO)
        delete testVAO;
    if (testVBO)
        delete testVBO;
}

void MeshLoadingLevel::Update(float deltaTime)
{
    if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
        std::cout << "Adding to movement speed\n";
    if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
        std::cout << "Removing from movement speed\n";
}

void MeshLoadingLevel::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.047058f, 0.047058f, 0.047058f, 1.0);
    glEnable(GL_DEPTH_TEST);

    // use light shader to render cubes and set uniforms where needed
    lightShader->use();

    // set Material properties: set texture units 
    mCubeTexture->activeTexture(0);
    mSpecularMapTexture->activeTexture(1);
    lightShader->setInt("uMaterial.diffuse", 0);
    lightShader->setInt("uMaterial.specular", 1);
    lightShader->setFloat("uMaterial.shininess", mCubeMaterial.specExp);

    // camera props 
    lightShader->setVec3fv("uCameraPos", glm::value_ptr(mainCamera.Position));
    // light properties
    lightShader->setVec3fv("uDirectionalLight.direction", glm::value_ptr(mDirectionalLight.direction));
    lightShader->setVec3fv("uDirectionalLight.ambient", glm::value_ptr(mDirectionalLight.ambient));
    lightShader->setVec3fv("uDirectionalLight.diffuse", glm::value_ptr(mDirectionalLight.diffuse));
    lightShader->setVec3fv("uDirectionalLight.specular", glm::value_ptr(mDirectionalLight.specular));

    view = mainCamera.GetViewMatrix();
    projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)mSceneInfo.mViewport.width / (float)mSceneInfo.mViewport.height, 0.1f, 100.0f);

    lightShader->setMat4fv("uView", glm::value_ptr(view));
    lightShader->setMat4fv("uProjection", glm::value_ptr(projection));

    // draw cubes
    for (int16_t i{}; i < 10; i++) {
        model = glm::translate(idMat, mCubePositions[i]);
        model = glm::rotate(model, static_cast<float>(i * 10), glm::vec3(1.0f, 0.3f, 0.25f));

        lightShader->setMat4fv("uModel", glm::value_ptr(model));

        testVAO->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        testVAO->Unbind();
    }
}
