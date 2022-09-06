#ifndef __HOUND_VEC3_H__
#define __HOUND_VEC3_H__

#include <glm/glm.hpp>


namespace Hound {
	#define VEC3_EPSILON 0.000001f

	struct vec3
	{
		union {
			struct {
				float x;
				float y;
				float z;
			};

			float v[3];
		};

		inline vec3()
			: x{ 0.0f }, y{ 0.0f }, z{ 0.f } {

		}

		inline vec3(float _value)
			: x{ _value }, y{ _value }, z{ _value } {

		}

		inline vec3(float _x, float _y, float _z)
			: x{ _x }, y{ _y }, z{ _z } {

		}

		inline vec3(float* fv)
			: x{ fv[0] }, y{ fv[1] }, z{ fv[2] } {

		}

		inline vec3(const glm::vec3& pGlmVec3) 
			: x{ pGlmVec3.x }, y{ pGlmVec3.y }, z{ pGlmVec3.z } {

		}

		// unary operations
		vec3& operator+=(const vec3& r);
		vec3& operator-=(const vec3& r);
		vec3& operator*=(const vec3& r);
		vec3& operator*=(const float value);
	};

	// unary operations
	vec3 operator-(const vec3& r);

	// binary operations
	vec3 operator+(const vec3& l, const vec3& r);
	vec3 operator-(const vec3& l, const vec3& r);
	vec3 operator*(const vec3& l, const vec3& r);
	vec3 operator*(const vec3& l, const float value);

	// comparison operators
	bool operator==(const vec3& l, const vec3& r);
	bool operator!=(const vec3& l, const vec3& r);

	// dot product
	float dot(const vec3& l, const vec3& r);
	// cross product
	vec3 cross(const vec3& l, const vec3& r);
	
	// to find the length of a vector
	float lenSq(const vec3& v);
	float len(const vec3& v);
	
	// distance between two vectors
	float distance(const vec3& l, const vec3& r);

	// normalizing vectors
	void normalize(vec3& v);
	vec3 normalized(const vec3& v);
	
	// angle between two un-normalized vectors
	float angle(const vec3& l, const vec3& r);

	// projection: this projects a unto b i.e ProjbA
	vec3 project(const vec3& a, const vec3& b);

	// rejection:  
	vec3 reject(const vec3& a, const vec3& b);

	// reflection
	vec3 reflect(const vec3& a, const vec3& b);

	// lerping
	// linear interpolation
	vec3 lerp(const vec3& s, const vec3& e, float t);
	// spherical interpolation
	vec3 slerp(const vec3& s, const vec3& e, float t);
	// nlerp
	vec3 nlerp(const vec3& s, const vec3& e, float t);
};

#endif
