#pragma once

#include "Transform.h"

class Shader;

class Entity
{
public:
	Entity() = default;
	virtual ~Entity() = default;

	virtual void Update() = 0;
	virtual void Render(Shader&) = 0;

	Transform& GetTransform() { return m_transform; }

protected:
	Transform m_transform;
};

