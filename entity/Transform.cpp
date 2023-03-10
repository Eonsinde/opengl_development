#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>


Transform::Transform()
	: m_translation{ 0.0f }, m_scale{ 1.0f } {

}

void Transform::SetRotation(const glm::mat3& rotation)
{

}

const glm::mat3& Transform::GetRotation() const
{
	return m_rotation;
}

void Transform::SetTranslation(const float translateBy)
{
	m_translation.x = translateBy;
	m_translation.y = translateBy;
	m_translation.z = translateBy;
}

void Transform::SetTranslation(const float x, const float y, const float z)
{
	m_translation.x = x;
	m_translation.y = y;
	m_translation.z = z;
}

void Transform::SetTranslation(const glm::vec3& translateBy)
{
	m_translation.x = translateBy.x;
	m_translation.y = translateBy.y;
	m_translation.z = translateBy.z;
}

void Transform::TranslateBy(const float x, const float y, const float z)
{
	m_translation.x += x;
	m_translation.y += y;
	m_translation.z += z;
}

const glm::vec3& Transform::GetTranslation() const
{
	// // O: insert return statement here
	return m_translation;
}

// uniform scaling
void Transform::SetScale(const float scaleBy)
{
	m_scale.x = scaleBy;
	m_scale.y = scaleBy;
	m_scale.z = scaleBy;
}

void Transform::SetScale(const float x, const float y, const float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

void Transform::SetScale(const glm::vec3& scaleBy)
{
	m_scale.x = scaleBy.x;
	m_scale.y = scaleBy.y;
	m_scale.z = scaleBy.z;
}

void Transform::ScaleBy(const float x, const float y, const float z)
{
	m_scale.x += x;
	m_scale.y += y;
	m_scale.z += z;
}

const glm::vec3& Transform::GetScale() const
{
	return m_scale;
}

void Transform::UpdateFinalMatrix()
{
	// build TRS matrix
	m_finalMatrix = glm::translate(glm::mat4(1.0f), m_translation);
	m_finalMatrix = glm::scale(m_finalMatrix, m_scale);
}

const glm::mat4& Transform::GetMatrix() 
{
	UpdateFinalMatrix();
	return m_finalMatrix;
}
