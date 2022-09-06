#ifndef __HOUND_VEC2_H__
#define __HOUND_VEC2_H__

#include <glm/glm.hpp>


namespace Hound {
#define VEC2_EPSILON 0.000001f

	template<typename T>
	struct TVec2
	{
		union {
			struct {
				T x;
				T y;
			};

			T v[2];
		};

		inline TVec2()
			: x{ (T)0 }, y{ (T)0 } {

		}

		inline TVec2(T _value)
			: x{ _value }, y{ _value } {

		}

		inline TVec2(T _x, T _y)
			: x{ _x }, y{ _y } {

		}

		inline TVec2(T* fv)
			: x{ fv[0] }, y{ fv[1] } {

		}

		inline TVec2(const glm::vec2& pGlmVec2)
			: x{ (T)pGlmVec2.x }, y{ (T)pGlmVec2.y } {

		}
	};

	typedef TVec2<float> vec2;
	typedef TVec2<int> ivec2;
};

#endif
