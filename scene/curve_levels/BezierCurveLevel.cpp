#include "BezierCurveLevel.h"

#include "../../core/Input.h"

#include "../../shaders/Shader.h"
#include "../../shaders/classes/LineShader.h"
#include "../../shaders/classes/PointShader.h"

#include "../../renderer/Draw.h"


void BezierCurveLevel::Init()
{
    pointShader1 = new PointShader();
    lineShader1 = new LineShader();

    // bind light VAO and bind buffer
    glGenVertexArrays(1, &VAO);

    // populate bezier curve attributes with data
    bezierCurve1.P1 = glm::vec3(-0.5f, 0.0f, 0.0f);
    bezierCurve1.P2 = glm::vec3(0.5f, 0.0f, 0.0f);
    bezierCurve1.C1 = glm::vec3(-0.2f, 0.1f, 0.0f);
    bezierCurve1.C2 = glm::vec3(0.2f, 0.1f, 0.0f);

    bezierCurve1.P1 += bezierCurve1.P2;
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
}

