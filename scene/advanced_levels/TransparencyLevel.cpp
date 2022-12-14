#include "TransparencyLevel.h"


#include "../../core/Input.h"

#include "../../shaders/Shader.h"



void TransparencyLevel::Init()
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

    float planeVertices[] = {
        // positions  // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
    };

    float windowVertices[] = {
        -0.5f,   0.5f,   0.0f,  0.0f, 1.0f,
        -0.5f,  -0.5f,   0.0f,  0.0f, 0.0f,
         0.5f,  -0.5f,   0.0f,  1.0f, 0.0f,
         0.5f,   0.5f,   0.0f,  1.0f, 1.0f,
        -0.5f,   0.5f,   0.0f,  0.0f, 1.0f,
         0.5f,  -0.5f,   0.0f,  1.0f, 0.0f,
    };

    windowPositions.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
    windowPositions.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
    windowPositions.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
    windowPositions.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
    windowPositions.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

    // CUBE: create VAOs
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    // create & register VBOs 
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // PLANE: create VAOs
    glGenVertexArrays(1, &planeVAO);
    glBindVertexArray(planeVAO);
    // create & register VBOs 
    glGenBuffers(1, &planeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // WINDOWS: create VAOs
    glGenVertexArrays(1, &glassVAO);
    glBindVertexArray(glassVAO);
    // create & register VBOs 
    glGenBuffers(1, &glassVBO);
    glBindBuffer(GL_ARRAY_BUFFER, glassVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(windowVertices), windowVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    /* cubeVBO.Set(vertices, 3, 36);
     cubeVAO.RegisterBuffer(cubeVBO);

     planeVBO.Set(planeVertices, 5, 6);
     planeVAO.RegisterBuffer(planeVBO);*/

    mainShader = new Shader("./shaders/codes/texture_.vert", "./shaders/codes/texture_.frag");
    glassShader = new Shader("./shaders/codes/texture_.vert", "./shaders/codes/transparency_.frag");

    mCubeTexture = new Hound::Texture("./assets/textures/brickwall.jpg");
    mPlaneTexture = new Hound::Texture("./assets/textures/metal.png");
    mGlassTexture = new Hound::Texture("./assets/textures/window.png");  

    // this algorithm is used to give the windows a drawing other from the farther to the nearest to support blending
    // using the camera's position as a point of reference, we subtract each windowPos from the cameraPos and get the 
    // length of the resultant vector
    // the data will be appended in the sorted_map from the leastest distance to the greatest
    // i.e 10.42f, 12.4f, 40.0f, 60.0f
    for (unsigned int i = 0; i < windowPositions.size(); i++)
    {
        float distance = glm::length(mainCamera.Position - windowPositions[i]);
        sorted[distance] = windowPositions[i];
    }
}

void TransparencyLevel::LoadScene()
{

}

void TransparencyLevel::UnloadScene()
{
    if (mainShader)
        delete mainShader;

    if (mCubeTexture)
        delete mCubeTexture;
    if (mPlaneTexture)
        delete mPlaneTexture;

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &planeVBO);
}

void TransparencyLevel::Update(float deltaTime)
{
    if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
        std::cout << "Adding to movement speed\n";
    if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
        std::cout << "Removing from movement speed\n";
}

void TransparencyLevel::Draw()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0784f, 0.0784f, 0.0784f, 1.0);

    //glPointSize(15.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // mode - GL_LINE, GL_FILL, GL_POINT 
    

    view = mainCamera.GetViewMatrix();
    projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)mSceneInfo.width / (float)mSceneInfo.height, 0.1f, 100.0f);

        
    mainShader->use();
    mCubeTexture->activeTexture(0);
    mainShader->setInt("texture_diffuse", 0);
    mainShader->setMat4fv("uView", glm::value_ptr(view));
    mainShader->setMat4fv("uProjection", glm::value_ptr(projection));

    // render cubes
    for (int16_t i{}; i < 2; i++) {
        model = glm::translate(idMat, mCubePositions[i]);
        mainShader->setMat4fv("uModel", glm::value_ptr(model));

        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }


    // draw the plane
    mPlaneTexture->activeTexture(1);
    mainShader->setInt("texture_diffuse", 1);
    //model = glm::translate(idMat, glm::vec3{ 0.0f, -15.0f, 0.0f });
    mainShader->setMat4fv("uModel", glm::value_ptr(idMat));

    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);


    glassShader->use();
    mGlassTexture->setWrappingPropetires(GL_CLAMP_TO_BORDER);
    mGlassTexture->activeTexture(0);
    glassShader->setInt("glass_diffuse", 0);
    glassShader->setMat4fv("uView", glm::value_ptr(view));
    glassShader->setMat4fv("uProjection", glm::value_ptr(projection));

    // render windows from farthest to nearest using sorted_map
    for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
    {
        model = glm::translate(idMat, it->second);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
        glassShader->setMat4fv("uModel", glm::value_ptr(model));

        glBindVertexArray(glassVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
}

