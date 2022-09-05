#pragma once


template<typename T>
class Bezier {
public:
	T P1; // Point 1
	T C1; // Control 1
	T P2; // Point 2
	T C2; // Control 2
};


template<typename T>
inline T Interpolate(Bezier<T>& curve, float t) {
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