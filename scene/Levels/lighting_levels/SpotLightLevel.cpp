#include "SpotLightLevel.h"

#include "../../shaders/Shader.h"
#include "../../core/Input.h"


void SpotLightLevel::Init()
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

    cubeShader = new Shader("./shaders/codes/basic.vert", "./shaders/codes/basic.frag");
    lightShader = new Shader("./shaders/codes/ADS.vert", "./shaders/codes/spotlight_ADS.frag");

    mCubeTexture = new Hound::Texture("./assets/textures/wooden_metallic_container.png");
    mSpecularMapTexture = new Hound::Texture("./assets/textures/wooden_metallic_specular_container.png");

    // spot light props
    //mSpotLight.position = glm::vec3(0.0f, 1.0f, 10.0f);
    mSpotLight.position = mainCamera.Position;
    mSpotLight.direction = mainCamera.Front;
    mSpotLight.ambient = glm::vec3(0.1f);
    mSpotLight.diffuse = glm::vec3(1.0f);
    mSpotLight.specular = glm::vec3(0.5f);
    // angles
    mSpotLight.cuterOff = glm::cos(glm::radians(12.5f)); // 0.976
    mSpotLight.outerCutOff = glm::cos(glm::radians(19.5f)); // 0.976
    // attenuation props
    mSpotLight.constant = 1.0f;
    mSpotLight.linear = 0.045f;
    mSpotLight.quadratic = 0.0075f;

    // material for cube
    mCubeMaterial.shininess = 32.0f;
}

void SpotLightLevel::LoadScene()
{

}

void SpotLightLevel::UnloadScene()
{
    if (lightShader)
        delete lightShader;
    if (cubeShader)
        delete cubeShader;
    if (mCubeTexture)
        delete mCubeTexture;

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &cubeVAO);
}

void SpotLightLevel::Update(float deltaTime)
{
    if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
        std::cout << "Adding to movement speed\n";
    if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
        std::cout << "Removing from movement speed\n";
}

void SpotLightLevel::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0784f, 0.0784f, 0.0784f, 1.0);
    glEnable(GL_DEPTH_TEST);

    // use light shader to render cubes and set uniforms where needed
    lightShader->use();

    // set Material properties
    mCubeTexture->activeTexture(0);
    mSpecularMapTexture->activeTexture(1);
    lightShader->setInt("uMaterial.diffuse", 0);
    lightShader->setInt("uMaterial.specular", 1);
    lightShader->setFloat("uMaterial.shininess", mCubeMaterial.shininess);

    // camera props 
    lightShader->setVec3fv("uCameraPos", glm::value_ptr(mainCamera.Position));
    // light positional props
    lightShader->setVec3fv("uSpotLight.position", glm::value_ptr(mainCamera.Position));
    lightShader->setVec3fv("uSpotLight.direction", glm::value_ptr(mainCamera.Front));
    // ADS light props
    lightShader->setVec3fv("uSpotLight.ambient", glm::value_ptr(mSpotLight.ambient));
    lightShader->setVec3fv("uSpotLight.diffuse", glm::value_ptr(mSpotLight.diffuse));
    lightShader->setVec3fv("uSpotLight.specular", glm::value_ptr(mSpotLight.specular));
    // angles
    lightShader->setFloat("uSpotLight.cuterOff", mSpotLight.cuterOff);
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

    //// use cube shader to render light cube
    //cubeShader->use();

    //cubeShader->setVec3fv("uPixelColor", glm::value_ptr(glm::vec3(1.0f)));

    //model = glm::scale(idMat, glm::vec3(0.5f));
    //// make the light rotate
    ///*mSpotLight.position.x = lightRotationRad * glm::sin(glfwGetTime());
    //mSpotLight.position.y = 0.0f;
    //mSpotLight.position.z = lightRotationRad * glm::cos(glfwGetTime());*/
    //model = glm::translate(model, mSpotLight.position); // firstly place it here and then ... 

    //cubeShader->setMat4fv("uModel", glm::value_ptr(model));
    //cubeShader->setMat4fv("uView", glm::value_ptr(view));
    //cubeShader->setMat4fv("uProjection", glm::value_ptr(projection));

    //glBindVertexArray(cubeVAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    //glBindVertexArray(0);
}

