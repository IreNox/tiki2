#pragma once

/* misc utility functions and constants */
const double   Pi        = 3.14159;
const double   TwoPi     = Pi * 2;


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



//returns a random double between zero and 1
inline float RandFloat() {return ((rand())/(RAND_MAX+1.0f));}

//returns a random double in the range -1 < n < 1
inline float RandomClamped()    {return RandFloat() - RandFloat();}
