#include "MultipleLightsLevel.h"

#include "../../shaders/Shader.h"
#include "../../core/Input.h"

//#include "../../modelLoader/OBJLoader.h"


void MultipleLightsLevel::Init()
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

    // bind light VAO and bind buffer
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    // bind cube VAO and register VBO data in it by binding the VBO 
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    // bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void MultipleLightsLevel::LoadScene()
{
    // create shaders
    cubeShader = new Shader("./shaders/codes/basic.vert", "./shaders/codes/basic.frag");
    lightShader = new Shader("./shaders/codes/ADS.vert", "./shaders/codes/multiple_lights_ADS.frag");

    // create textures
    mCubeTexture = new Hound::Texture("./assets/textures/wooden_metallic_container.png");
    mSpecularMapTexture = new Hound::Texture("./assets/textures/wooden_metallic_specular_container.png");

    // directional light props
    mDirLight.direction = mainCamera.Front;
    mDirLight.ambient = glm::vec3(0.1f);
    mDirLight.diffuse = glm::vec3(1.0f);
    mDirLight.specular = glm::vec3(0.5f);
    mDirLight.constant = 1.0f;
    mDirLight.linear = 0.045f;
    mDirLight.quadratic = 0.0075f;

    // point lights props
    pointLights.reserve(4);
    // creating the point lights: P1
    Hound::PointLight pointLight1;
    pointLight1.position = mainCamera.Position;
    pointLight1.ambient = glm::vec3(0.1f);
    pointLight1.diffuse = glm::vec3(1.0f, 0.3f, 0.5f);
    pointLight1.specular = glm::vec3(0.5f);
    pointLight1.constant = 1.0f;
    pointLight1.linear = 0.045f;
    pointLight1.quadratic = 0.0075f;
    pointLights.push_back(pointLight1);
    // P2
    Hound::PointLight pointLight2;
    pointLight2.position = mainCamera.Position;
    pointLight2.ambient = glm::vec3(0.1f);
    pointLight2.diffuse = glm::vec3(0.6f, 1.0f, 0.2f);
    pointLight2.specular = glm::vec3(0.5f);
    pointLight2.constant = 1.0f;
    pointLight2.linear = 0.045f;
    pointLight2.quadratic = 0.0075f;
    pointLights.push_back(pointLight2);
    // P3
    Hound::PointLight pointLight3;
    pointLight3.position = mainCamera.Position;
    pointLight3.ambient = glm::vec3(0.1f);
    pointLight3.diffuse = glm::vec3(0.3f, 0.6f, 1.0f);
    pointLight3.specular = glm::vec3(0.5f);
    pointLight3.constant = 1.0f;
    pointLight3.linear = 0.045f;
    pointLight3.quadratic = 0.0075f;
    pointLights.push_back(pointLight3);
    // P4
    Hound::PointLight pointLight4;
    pointLight4.position = mainCamera.Position;
    pointLight4.ambient = glm::vec3(0.1f);
    pointLight4.diffuse = glm::vec3(1.0f);
    pointLight4.specular = glm::vec3(0.5f);
    pointLight4.constant = 1.0f;
    pointLight4.linear = 0.045f;
    pointLight4.quadratic = 0.0075f;
    pointLights.push_back(pointLight4);

    // spot light props
    //mSpotLight.position = glm::vec3(0.0f, 1.0f, 10.0f);
    mSpotLight.position = mainCamera.Position;
    mSpotLight.direction = mainCamera.Front;
    mSpotLight.ambient = glm::vec3(0.1f);
    mSpotLight.diffuse = glm::vec3(1.0f);
    mSpotLight.specular = glm::vec3(0.5f);
    mSpotLight.cuterOff = glm::cos(glm::radians(12.5f)); // 0.976
    mSpotLight.outerCutOff = glm::cos(glm::radians(19.5f)); // 0.976
    mSpotLight.constant = 1.0f;
    mSpotLight.linear = 0.045f;
    mSpotLight.quadratic = 0.0075f;


    // material for cube
    mCubeMaterial.specExp = 32.0f;

    // testing 
    //Hound::loadObjMesh("./input_test_file.txt");
}

void MultipleLightsLevel::UnloadScene()
{
    if (lightShader)
        delete lightShader;
    if (cubeShader)
        delete cubeShader;

    if (mCubeTexture)
        delete mCubeTexture;
    if (mSpecularMapTexture)
        delete mSpecularMapTexture;

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &cubeVAO);
}

void MultipleLightsLevel::Update(float deltaTime)
{
    if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
        std::cout << "Adding to movement speed\n";
    if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
        std::cout << "Removing from movement speed\n";
}

void MultipleLightsLevel::Draw()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0784f, 0.0784f, 0.0784f, 1.0);

    //glPointSize(15.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // mode - GL_LINE, GL_FILL, GL_POINT 

    // use light shader to render cubes and set uniforms where needed
    lightShader->use();

    // set Material properties
    mCubeTexture->activeTexture(0);
    mSpecularMapTexture->activeTexture(1);
    lightShader->setInt("uMaterial.diffuse", 0);
    lightShader->setInt("uMaterial.specular", 1);
    lightShader->setFloat("uMaterial.shininess", mCubeMaterial.specExp);

    // camera props 
    lightShader->setVec3fv("uCameraPos", glm::value_ptr(mainCamera.Position));
    // light positional props
    lightShader->setVec3fv("uSpotLight.position", glm::value_ptr(mainCamera.Position));
    lightShader->setVec3fv("uSpotLight.direction", glm::value_ptr(mainCamera.Front));
    // ADS light props
    lightShader->setVec3fv("uSpotLight.ambient", glm::value_ptr(mSpotLight.ambient));
    lightShader->setVec3fv("uSpotLight.diffuse", glm::value_ptr(mSpotLight.diffuse));
    lightShader->setVec3fv("uSpotLight.specular", glm::value_ptr(mSpotLight.specular));
    // light angles props
    lightShader->setFloat("uSpotLight.cuterOff", mSpotLight.cuterOff);
    lightShader->setFloat("uSpotLight.outerCutOff", mSpotLight.outerCutOff);
    // light attenuation props
    lightShader->setFloat("uSpotLight.constant", mSpotLight.constant);
    lightShader->setFloat("uSpotLight.linear", mSpotLight.linear);
    lightShader->setFloat("uSpotLight.quadratic", mSpotLight.quadratic);

    view = mainCamera.GetViewMatrix();
    projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)mSceneInfo.width / (float)mSceneInfo.height, 0.1f, 100.0f);

    lightShader->setMat4fv("uView", glm::value_ptr(view));
    lightShader->setMat4fv("uProjection", glm::value_ptr(projection));

    for (int16_t i{}; i < 10; i++) {
        model = glm::translate(idMat, mCubePositions[i]);
        model = glm::rotate(model, static_cast<float>(i * 10), glm::vec3(1.0f, 0.3f, 0.25f));

        lightShader->setMat4fv("uModel", glm::value_ptr(model));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}

