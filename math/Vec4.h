#ifndef __HOUND_VEC4_H__
#define __HOUND_VEC4_H__

#include <glm/glm.hpp>


namespace Hound {
#define VEC4_EPSILON 0.000001f

	template<typename T>
	struct TVec4
	{
		union {
			struct {
				T x;
				T y;
				T z;
				T w;
			};

			T v[4];
		};

		inline TVec4()
			: x{ (T)0 }, y{ (T)0 }, z{ (T)0 }, w{ (T)0 } {

		}

		inline TVec4(T _value)
			: x{ _value }, y{ _value }, z{ _value }, w{ (T)0 } {

		}

		inline TVec4(T _x, T _y, T _z, T _w)
			: x{ _x }, y{ _y }, z{ _z }, w{ _w } {

		}

		inline TVec4(T* fv)
			: x{ fv[0] }, y{ fv[1] }, z{ fv[2] }, w{ fv[3] } {

		}

		inline TVec4(const glm::vec4& pGlmVec4)
			: x{ (T)pGlmVec4.x }, y{ (T)pGlmVec4.y }, z{ (T)pGlmVec4.z }, w{ (T)pGlmVec4.w } {

		}
	};

	typedef TVec4<float> vec4;
	typedef TVec4<int> ivec4;
	typedef TVec4<unsigned int> uivec4;
};

#endif
