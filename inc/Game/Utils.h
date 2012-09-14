#pragma once

/* misc utility functions and constants */

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