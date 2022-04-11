#include "BasicLightingLevel.h"

#include "../../shaders/Shader.h"
#include "../../core/Input.h"



void BasicLightingLevel::Init()
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
    lightShader = new Shader("./shaders/codes/ASD.vert", "./shaders/codes/ASD.frag");

    mPointLight.position = glm::vec3(0.0f, 1.0f, 10.0f);
}

void BasicLightingLevel::LoadScene()
{

}

void BasicLightingLevel::UnloadScene()
{
    if (lightShader)
        delete lightShader;
    if (cubeShader)
        delete cubeShader;

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &cubeVAO);
}

void BasicLightingLevel::Update(float deltaTime)
{
    if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
        std::cout << "Adding to movement speed\n";
    if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
        std::cout << "Removing from movement speed\n";
}

void BasicLightingLevel::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0784f, 0.0784f, 0.0784f, 1.0);
    glEnable(GL_DEPTH_TEST);

    // use light shader to render cubes and set uniforms where needed
    lightShader->use();

    lightShader->setVec3fv("uPixelColor", glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
    // camera and light properties
    lightShader->setVec3fv("uCameraPos", glm::value_ptr(mainCamera.Position));
    lightShader->setVec3fv("uLightPos", glm::value_ptr(mPointLight.position));
    lightShader->setVec3fv("uLightColor", glm::value_ptr(glm::vec3(1.0f)));

    // x + Rsin@, y + Rcos@ - formula to get points of a circle
    //view = glm::translate(idMat, glm::vec3(5.0f * glm::sin(glfwGetTime()), 0.0f, 5.0f * glm::cos(glfwGetTime())));
    
    // make the camera move with the light
    //mainCamera.Position = mPointLight.position;
    // push it backwards to prevent overlapping with the light
   /* mainCamera.Position.x += 10.0f;
    mainCamera.Position.z += 10.0f;*/

    view = mainCamera.GetViewMatrix();
    projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)mSceneInfo.width / (float)mSceneInfo.height, 0.1f, 100.0f);

    lightShader->setMat4fv("uView", glm::value_ptr(view));
    lightShader->setMat4fv("uProjection", glm::value_ptr(projection));

    for (int16_t i{}; i < 10; i++) {
        //model = glm::scale(idMat, glm::vec3(1.0f, 1.0f, 1.0f));
        //model = glm::rotate(idMat, i*10, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::translate(idMat, mCubePositions[i]);
        model = glm::rotate(model, static_cast<float>(i * 10), glm::vec3(1.0f, 0.3f, 0.25f));
        
        lightShader->setMat4fv("uModel", glm::value_ptr(model));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

    // use cube shader to render light cube
    cubeShader->use();

    cubeShader->setVec3fv("uPixelColor", glm::value_ptr(glm::vec3(1.0f)));

    model = glm::scale(idMat, glm::vec3(0.5f));
    // make the light rotate
    mPointLight.position.x = lightRotationRad * glm::sin(glfwGetTime());
    mPointLight.position.y = 0.0f;
    mPointLight.position.z = lightRotationRad * glm::cos(glfwGetTime());
    model = glm::translate(model, mPointLight.position);
    model = glm::translate(model, mPointLight.position); // firstly place it here and then ... 

    cubeShader->setMat4fv("uModel", glm::value_ptr(model));
    cubeShader->setMat4fv("uView", glm::value_ptr(view));
    cubeShader->setMat4fv("uProjection", glm::value_ptr(projection));

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
