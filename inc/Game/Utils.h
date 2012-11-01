#pragma once

#include <random>
#include "Core/Matrix3x3.h"
#include "Core/TypeDef.h"

/* misc utility functions and constants */
const float   Pi        = 3.14159f;
const float   TwoPi     = Pi * 2;
const float	  Eps		= 10e-5f;

inline Double DegsToRads(double degrees)
{
  return degrees * 0.0174532925;
}

inline Double RadsToDegs(double radians)
{
  return radians * 57.2957795;
}

//returns the maximum of two values
template <class T>
inline T MaxOf(const T& a, const T& b)
{
  if (a>b) return a; return b;
}

//returns the minimum of two values
template <class T>
inline T MinOf(const T& a, const T& b)
{
  if (a<b) return a; return b;
}

inline float ABS(float x)
{
	return x < 0 ? (-x) : x;
}

inline bool ApproxEqual(float x, float v)
{
	return ABS(x - v) <= 0.001f ? true : false;
}

inline float LERP(float a, float b, float c)
{
	return b + a * (c-b);
}

inline float Min3(float a, float b, float c)
{
	return ( ( (a<b) && (a<c) ) ? a : ( (b<c) ? b : c) );
}

inline float Max3(float a, float b, float c)
{
	return ( ( (a>b) && (a>c) ) ? a : ( (b>c) ? b : c) );
}

// Extract X,Y,Z signs as 0..7 or 0...63 integer
inline int Sign3(Vector3 a)
{
	return ((a.X < Eps) ? 4 : 0 | (a.X > -Eps) ? 32 : 0 | 
		    (a.Y < Eps) ? 2 : 0 | (a.Y > -Eps) ? 16 : 0 | 
			(a.Z < Eps) ? 1 : 0 | (a.Z > -Eps) ? 8 : 0	);
}

//returns a random float between zero and 1
inline float RandFloat() {return ((rand())/(RAND_MAX+1.0f));}

//returns a random float in the range -1 < n < 1
inline float RandomClamped() {return RandFloat() - RandFloat();}



#pragma region Transforms2D
//  Transforms a point from the objects's local space into world space
inline Vector2 PointToWorldSpace(const Vector2 &point,
                                 const Vector2 &heading,
                                 const Vector2 &side,
                                 const Vector2 &position)
{
	//make a copy of the point
	Vector2 transPoint = point;
  
	// create a transformation matrix
	Matrix3x3 matTransform = matTransform.Rotate(heading, side) *
							 matTransform.Translate(position.X, position.Y);

	//now transform the vertices
	matTransform.TransformVector(transPoint);

    return transPoint;
}
#pragma endregion