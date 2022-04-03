#include "CubeLevel.h"
#include "../../shaders/Shader.h"
#include "../../core/Input.h"




void CubeLevel::Init()
{
    float vertices[] = {
      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,

      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,

       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,

      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
    };

    // create VAO and bind buffer
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    mShader = new Shader("./shaders/codes/basic.vert", "./shaders/codes/basic.frag");
}

void CubeLevel::LoadScene()
{

}

void CubeLevel::UnloadScene()
{
    if (mShader)
        delete mShader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void CubeLevel::Update(float deltaTime)
{
    if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
        std::cout << "Adding to movement speed\n";
    if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
        std::cout << "Removing from movement speed\n";
}

void CubeLevel::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0784f, 0.0784f, 0.0784f, 1.0);
    glEnable(GL_DEPTH_TEST);

    // use shader and set uniforms where needed
    mShader->use();
    
    mShader->setVec3fv("uPixelColor", glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));

    model = glm::scale(idMat, glm::vec3(1.0f, 1.0f, 1.0f));
    // x + Rsin@, y + Rcos@ - formula to get points of a circle
    //view = glm::translate(idMat, glm::vec3(5.0f * glm::sin(glfwGetTime()), 0.0f, 5.0f * glm::cos(glfwGetTime())));
    view = mainCamera.GetViewMatrix();
    //projection = glm::perspective(glm::radians(45.0f), (float)mSceneInfo.width / (float)mSceneInfo.height, 0.1f, 100.0f);
    projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)mSceneInfo.width / (float)mSceneInfo.height, 0.1f, 100.0f);

    mShader->setMat4fv("uModel", glm::value_ptr(model));
    mShader->setMat4fv("uView", glm::value_ptr(view));
    mShader->setMat4fv("uProjection", glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
