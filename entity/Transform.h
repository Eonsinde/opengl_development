#pragma once

#include <glm/glm.hpp>


class Transform
{
private:
	glm::vec3			m_translation;
	glm::vec3			m_scale;
	glm::vec3			m_rotation;
	glm::mat4			m_finalMatrix;

public:
	Transform();
	~Transform() = default;

	void				SetRotation(const float);
	void				SetRotation(const float, const float, const float);
	void				SetRotation(const glm::vec3&);
	void				RotateBy(const float, const float, const float);
	const glm::vec3&	GetRotation() const;

	void				SetTranslation(const float);
	void				SetTranslation(const float, const float, const float);
	void				SetTranslation(const glm::vec3&);
	void				TranslateBy(const float, const float, const float);
	const glm::vec3&	GetTranslation() const;

	void				SetScale(const float);
	void				SetScale(const float, const float, const float);
	void				SetScale(const glm::vec3&);
	void				ScaleBy(const float, const float, const float);
	const glm::vec3&	GetScale() const;

	void				UpdateFinalMatrix();
	const glm::mat4&	GetMatrix();
};

