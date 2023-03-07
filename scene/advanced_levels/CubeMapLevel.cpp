#include "CubeMapLevel.h"

#include "../../core/Input.h"

#include "../../shaders/Shader.h"


//VertexArray cubeVAO, planeVAO, glassVAO;
//VertexBuffer cubeVBO, planeVBO, glassVBO;


void CubeMapLevel::Init()
{
    float vertices[] = {
        // back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right              
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left                
        // front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right        
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left        
        // left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left       
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        // right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right          
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
        // bottom face          
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left        
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        // top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right                 
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // top-left              
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

    // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates. NOTE that this plane is now much smaller and at the top of the screen
    float quadVertices[] = {
        // positions   // texCoords
        -0.3f,  1.0f,  0.0f, 1.0f,
        -0.3f,  0.2f,  0.0f, 0.0f,
         0.3f,  0.2f,  1.0f, 0.0f,

        -0.3f,  1.0f,  0.0f, 1.0f,
         0.3f,  0.2f,  1.0f, 0.0f,
         0.3f,  1.0f,  1.0f, 1.0f
    };


    // CUBE: create VAO
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    // create & register VBO
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // PLANE: create VAO
    glGenVertexArrays(1, &planeVAO);
    glBindVertexArray(planeVAO);
    // create & register VBO
    glGenBuffers(1, &planeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // QUAD: create VAO
    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);
    // create & register VBO
    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // create front framebuffer
    glGenFramebuffers(1, &frameBuffer[0]);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer[0]);

    /*std::cout << "Res width: " << mSceneInfo.mViewport.width << "\n";
    std::cout << "Res Height: " << mSceneInfo.mViewport.height << "\n";*/

    // create texture that stores colors and attach it to framebuffer
    glGenTextures(1, &textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0); // attach texture to the buffer

    // create render buffer that stores depth(24) & stencil(8) 
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO); // now actually attach it

    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /*cubeVBO.Set(vertices, 3, 36);
    cubeVAO.RegisterBuffer(cubeVBO);

    planeVBO.Set(planeVertices, 5, 6);
    planeVAO.RegisterBuffer(planeVBO);

    glassVBO.Set(planeVertices, 2, 6);
    glassVAO.RegisterBuffer(glassVBO);*/

    mainShader = new Shader("./shaders/codes/texture_.vert", "./shaders/codes/texture_.frag");
    //fbQuadShader = new Shader("./shaders/codes/framebuffer_quad.vert", "./shaders/pp_codes/inversion_effect.frag");
    //fbQuadShader = new Shader("./shaders/codes/framebuffer_quad.vert", "./shaders/pp_codes/grayscale_effect.frag");
    //fbQuadShader = new Shader("./shaders/codes/framebuffer_quad.vert", "./shaders/pp_codes/kernel.frag");
    fbQuadShader = new Shader("./shaders/codes/framebuffer_quad.vert", "./shaders/codes/just_texture.frag");

    mCubeTexture = new Hound::Texture("./assets/textures/brickwall.jpg");
    mPlaneTexture = new Hound::Texture("./assets/textures/metal.png");
}

void CubeMapLevel::LoadScene()
{

}

void CubeMapLevel::UnloadScene()
{
    if (mainShader)
        delete mainShader;

    if (mCubeTexture)
        delete mCubeTexture;
    if (mPlaneTexture)
        delete mPlaneTexture;

    glDeleteTextures(1, &textureColorBuffer);
    glDeleteRenderbuffers(1, &RBO);
    glDeleteFramebuffers(1, &frameBuffer[0]);
}

void CubeMapLevel::Update(float deltaTime)
{
    if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
        std::cout << "Adding to movement speed\n";
    if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
        std::cout << "Removing from movement speed\n";
}

void CubeMapLevel::Draw()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // mode - GL_LINE, GL_FILL, GL_POINT

    /// <summary>
    /// First render pass
    /// offscreen rendering to frame buffer occurs here
    /// </summary>
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer[0]);
    glEnable(GL_DEPTH_TEST);

    // make sure we clear the framebuffer's content
    glClearColor(0.04f, 0.04f, 0.04f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainCamera.Yaw += 180.0f;
    mainCamera.ProcessMouseMovement(0, 0, false);
    view = mainCamera.GetViewMatrix();
    // reset the rotation given to the camera
    mainCamera.Yaw -= 180.0f;
    mainCamera.ProcessMouseMovement(0, 0, true);
    projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);

    mainShader->use();
    mCubeTexture->activeTexture(0);
    mainShader->setInt("texture_diffuse", 0);
    mainShader->setMat4fv("uView", glm::value_ptr(view));
    mainShader->setMat4fv("uProjection", glm::value_ptr(projection));

    // render cubes
    for (int16_t i{}; i < 2; i++)
    {
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


    /// <summary>
    /// Second render pass
    /// onscreen rendering to default frame buffer occurs here
    /// </summary>
    // switch back to default frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0784f, 0.0784f, 0.0784f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // the camera is now facing it's default position(i.e no rotations by 180)
    // update the uView attribute in your shader 
    view = mainCamera.GetViewMatrix();
    projection = glm::perspective(glm::radians(mainCamera.Zoom), (float)mSceneInfo.mViewport.width / (float)mSceneInfo.mViewport.height, 0.1f, 100.0f);

    mainShader->setMat4fv("uView", glm::value_ptr(view));
    mainShader->setMat4fv("uProjection", glm::value_ptr(projection));


    mCubeTexture->activeTexture(0);
    mainShader->setInt("texture_diffuse", 0);

    // render cubes
    for (int16_t i{}; i < 2; i++)
    {
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


    // draw framebuffer quad using the default framebuffer
    // the quad is draw over the entire scene and depth testing is disabled to ensure this
    glDisable(GL_DEPTH_TEST);
    // put texture in unit 2
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer); // use the color attachment texture as the texture of the quad plane
    // use the quad shader
    fbQuadShader->use();
    fbQuadShader->setInt("screenTexture", 2);
    // draw quad
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

