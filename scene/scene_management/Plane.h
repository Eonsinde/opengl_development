#ifndef __HOUND_PLANE_H__
#define __HOUND_PLANE_H__

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Camera.h"


// to explain how the SimplePlane class works:
// a plane is defined by a normal and a point 
// The buildPlane method helps to construct our arbitrary plane
// and defines its' distance from the origin(0,0,) 
// the IsInFront method is then used to see if a certain point 
// is on the plane or behind it and uses the already computed distance to achieve this
class SimplePlane {
public:
	SimplePlane() = default;
	SimplePlane(const glm::vec3& pPoint, const glm::vec3& pNormal)
		: m_normal{ pNormal }, m_distance{ glm::dot(pPoint, pNormal)} {

	}
	~SimplePlane() = default;

	void BuildPlane(const glm::vec3& pPoint, const glm::vec3& pNormal) {
		m_normal = glm::normalize(pNormal);
		m_distance = glm::dot(pPoint, m_normal);
	}

	bool IsInFront(const glm::vec4& pPoint) const {
		return IsInFront(glm::vec3(pPoint.x, pPoint.y, pPoint.z));
	}

	bool IsInFront(const glm::vec3& pPoint) const {
		// if m_normal * pPoint >= m_distance: object is in front else : not in front
		return glm::dot(m_normal, pPoint) >= m_distance;
	}

private:
	glm::vec3 m_normal;
	float m_distance;
};


class MPlane
{
public:
	MPlane() 
		: x(), y(), z(), mDistance() {
	}

	MPlane(float _x, float _y, float _z, float _distance)
		: x{ _x }, y{ _y }, z{ _z }, mDistance{ _distance } {
		
	}

	~MPlane() = default;

	float x, y, z, mDistance;
};


struct Plane
{
	friend std::ostream& operator<<(std::ostream& os, Plane& rhsObj);

	Plane() = default;
	Plane(const glm::vec3& point, const glm::vec3& norm)
		: normal(glm::normalize(norm)),	distance(glm::dot(normal, point))
		{

	}

	float getSignedDistanceToPlane(const glm::vec3& point) const
	{
		return glm::dot(normal, point) - distance;
	}

	glm::vec3 normal = { 0.f, 1.f, 0.f }; // unit vector
	float     distance = 0.f;        // Distance with origin
};

std::ostream& operator<<(std::ostream& os, Plane& rhsObj) {
	os << "Normal: " << rhsObj.normal.x << " " << rhsObj.normal.y << " " << rhsObj.normal.z << '\n';
	os << "Distance: " << rhsObj.distance << '\n';
	return os;
}


struct Frustum
{
    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Plane farFace;
    Plane nearFace;
};

Frustum createFrustumFromCamera(const Hound::Camera& cam, float aspect, float fovY,	float zNear, float zFar)
{
	// sample arugments: camObj, (1280/720), 45.0f, 0.1f, 100.0f
	Frustum     frustum;
	const float halfVSide = zFar * tanf(fovY * .5f);
	const float halfWSide = halfVSide * aspect;
	const glm::vec3 frontMultFar = zFar * cam.Front; // implies front multipled by zFar

	frustum.nearFace = { cam.Position + zNear * cam.Front, cam.Front };
	frustum.farFace = { cam.Position + frontMultFar, -cam.Front };
	frustum.rightFace = { cam.Position,
							glm::cross(cam.Up,frontMultFar + cam.Right * halfWSide) };
	frustum.leftFace = { cam.Position,
							glm::cross(frontMultFar - cam.Right * halfWSide, cam.Up) };
	frustum.topFace = { cam.Position,
							glm::cross(cam.Right, frontMultFar - cam.Up * halfVSide) };
	frustum.bottomFace = { cam.Position,
							glm::cross(frontMultFar + cam.Up * halfVSide, cam.Right) };

	return frustum;
}

#endif

