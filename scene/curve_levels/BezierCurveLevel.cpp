#include "BezierCurveLevel.h"

#include "../../core/Input.h"

#include "../../shaders/Shader.h"
#include "../../shaders/classes/LineShader.h"
#include "../../shaders/classes/PointShader.h"

#include "../../renderer/VertexArray.h"
#include "../../renderer/buffers/VertexBuffer.h"

#include "../../renderer/Draw.h"

#include "../../math/Interpolation.h"


void BezierCurveLevel::Init()
{
    pointShader1 = new PointShader();
    lineShader1 = new LineShader();

    // create points VAO
    glGenVertexArrays(1, &VAO);

    // populate bezier curve attributes with data
    bezierCurve1.P1 = glm::vec3(-0.5f, 0.0f, 0.0f);
    bezierCurve1.P2 = glm::vec3(0.5f, 0.0f, 0.0f);
    bezierCurve1.C1 = glm::vec3(-0.2f, 0.5f, 0.0f);
    bezierCurve1.C2 = glm::vec3(0.2f, 0.5f, 0.0f);

    //bezierCurve1.P1 += bezierCurve1.P2;
}

void BezierCurveLevel::LoadScene()
{

}

void BezierCurveLevel::UnloadScene()
{
    if (pointShader1)
        delete pointShader1;

    if (lineShader1)
        delete lineShader1;

    glDeleteVertexArrays(1, &VAO);
}

void BezierCurveLevel::Update(float deltaTime)
{
    if (Hound::Input::IsKeyPressed(Hound::Key::KPAdd))
        std::cout << "Adding to movement speed\n";
    if (Hound::Input::IsKeyPressed(Hound::Key::KPSubtract))
        std::cout << "Removing from movement speed\n";
}

void BezierCurveLevel::Draw()
{
    glClearColor(0.0784f, 0.0784f, 0.0784f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(8.0f);

    pointShader1->use();
    glBindVertexArray(VAO);
    // render points using pointshader 
    pointShader1->setVec3fv("uPixelColor", glm::value_ptr(blue));
    DrawPoint(bezierCurve1.P1);
    pointShader1->setVec3fv("uPixelColor", glm::value_ptr(blue));
    DrawPoint(bezierCurve1.P2);
    pointShader1->setVec3fv("uPixelColor", glm::value_ptr(red));
    DrawPoint(bezierCurve1.C1);
    pointShader1->setVec3fv("uPixelColor", glm::value_ptr(red));
    DrawPoint(bezierCurve1.C2);
    glBindVertexArray(0);

    lineShader1->use();

    lineShader1->setVec3fv("uPixelColor", glm::value_ptr(yellow));
    DrawLine(bezierCurve1.P1, bezierCurve1.C1);
    DrawLine(bezierCurve1.C1, bezierCurve1.C2);
    DrawLine(bezierCurve1.C2, bezierCurve1.P2);

    pointShader1->setVec3fv("uPixelColor", glm::value_ptr(magenta));
    pointShader1->use();
    for (uint16_t i{}; i < 10.0f; i++) {
        std::cout << "t per time: " << i << "\n";
        auto point = interpolate(bezierCurve1, i/10.0f);
        std::cout << point.x << " " << point.y << " " << point.z << "\n";
        glBindVertexArray(VAO);
        DrawPoint(point);
        glBindVertexArray(0);
    }

    // render fun circle
    glm::vec3 prevPos { 0.5f, 0.0f, 0.0f };
    glm::vec3 nextPos;

    lineShader1->use();
    lineShader1->setVec3fv("uPixelColor", glm::value_ptr(magenta));
    for (uint16_t i{}; i < 360; i++) {
        nextPos = glm::vec3{
            0.0f + 0.5f * glm::cos(glm::radians((float)i)), // x
            0.0f + 0.5f * glm::sin(glm::radians((float)i)), // y
            0.0f
        };

        DrawLine(prevPos, nextPos);
        prevPos = nextPos;
    }
}

