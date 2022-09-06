#include "Vec3.h"



namespace Hound {
	// member functions
	vec3& vec3::operator+=(const vec3& r)
	{
		this->x += r.x;
		this->y += r.y;
		this->z += r.z;

		return *this;
	}

	vec3& vec3::operator-=(const vec3& r)
	{
		this->x -= r.x;
		this->y -= r.y;
		this->z -= r.z;

		return *this;
	}

	vec3& vec3::operator*=(const vec3& r)
	{
		this->x *= r.x;
		this->y *= r.y;
		this->z *= r.z;

		return *this;
	}

	vec3& vec3::operator*=(const float value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;

		return *this;
	}

	// overloaded non member functions
	// unary 
	vec3 operator-(const vec3& r)
	{
		return vec3{
			-r.x,
			-r.y,
			-r.z
		};
	}

	// binary
	vec3 operator+(const vec3& l, const vec3& r)
	{
		return vec3(l.x + r.x, l.y + r.y, l.z + r.z);
	}

	vec3 operator-(const vec3& l, const vec3& r)
	{
		return vec3(l.x - r.x, l.y - r.y, l.z - r.z);
	}

	vec3 operator*(const vec3& l, const vec3& r)
	{
		return vec3(l.x * r.x, l.y * r.y, l.z * r.z);
	}

	vec3 operator*(const vec3& l, const float value)
	{
		return vec3(l.x * value, l.y * value, l.z * value);
	}

	// special vector functions
	float dot(const vec3& l, const vec3& r)
	{
		return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
	}

	vec3 cross(const vec3& l, const vec3& r)
	{
		return vec3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
	}

	float lenSq(const vec3& v)
	{
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}

	float len(const vec3& v)
	{
		float lenSq = v.x *	v.x + v.y * v.y + v.z *	v.z;

		if (lenSq <	VEC3_EPSILON) 
		{
			return 0.0f;
		}
		
		return sqrtf(lenSq);
	}

	float distance(const vec3& l, const vec3& r)
	{
		return len(l - r);
	}

	void normalize(vec3& v) {
		float lenSq = v.x *	v.x + v.y * v.y + v.z *	v.z;

		if (lenSq <	VEC3_EPSILON) {
			return;
		}

		float invLen = 1.0f / sqrtf(lenSq);

		v.x *= invLen;
		v.y *= invLen;
		v.z *= invLen;
	}

	vec3 normalized(const vec3& v)
	{
		float lenSq = v.x *	v.x + v.y * v.y + v.z *	v.z;

		if (lenSq <	VEC3_EPSILON) {
			return v;
		}

		float invLen = 1.0f	/ sqrtf(lenSq);

		return vec3(
			v.x * invLen,
			v.y * invLen,
			v.z * invLen
		);
	}

	float angle(const vec3& l, const vec3& r)
	{ 
		// formula: (l . r) / (|l| * |r|)

		float sqMagL = l.x * l.x + l.y * l.y + l.z * l.z; 
		float sqMagR = r.x * r.x + r.y * r.y + r.z * r.z;

		if (sqMagL < VEC3_EPSILON || sqMagR < VEC3_EPSILON) 
		{
			return 0.0f;
		}

		float dot = l.x * r.x + l.y * r.y + l.z * r.z;
		float len = sqrtf(sqMagL) * sqrtf(sqMagR);

		return acosf(dot / len);
	}

	vec3 project(const vec3& a, const vec3& b)
	{
		float magBSq = len(b);

		if (magBSq < VEC3_EPSILON) {
			return vec3();
		}

		float scale = dot(a, b) / magBSq;
		
		return b * scale;
	}

	vec3 reject(const vec3& a, const vec3& b)
	{
		vec3 projection = project(a, b);
		return a - projection;
	}

	vec3 reflect(const vec3& a, const vec3& b)
	{
		float magBSq = len(b);

		if (magBSq < VEC3_EPSILON) 
		{ 
			return vec3(); 
		}
		
		float scale = dot(a, b) / magBSq; 
		vec3 proj2 = b * (scale * 2); 
		
		return a - proj2;
	}
};


