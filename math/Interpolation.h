#ifndef __HOUND_INTERPOLATION__
#define __HOUND_INTERPOLATION__

#include "./curves/Bezier.h"

enum class InterpolationType {
	Constant,
	Linear,
	Cubic
};

template<typename T>
T lerp(T point1, T point2, float t) {
	return point1 * (1.0f - t) + point2 * t;
}

template<typename T>
inline T interpolate(Bezier<T>& curve, float t) {
	T pointA = lerp(curve.P1, curve.C1, t);
	T pointC = lerp(curve.C1, curve.C2, t);
	T pointB = lerp(curve.C2, curve.P2, t);

	// using the points now
	T pointE = lerp(pointA, pointC, t);
	T pointF = lerp(pointC, pointB, t);
	// the point R on our bezier curve
	T pointR = lerp(pointE, pointF, t);

	return pointR;
}

//template<typename T>
//inline T Interpolate(Bezier<T>& curve, float t) {
//	T pointA = lerp(curve.P1, curve.C1, t);
//	T pointC = lerp(curve.C1, curve.C2, t);
//	T pointB = lerp(curve.C2, curve.P2, t);
//
//	// using the points now
//	T pointE = lerp(pointA, pointC, t);
//	T pointF = lerp(pointC, pointB, t);
//	// the point R on our bezier curve
//	T pointR = lerp(pointE, pointF, t);
//
//	return pointR;
//}

#endif