#include <cmath>
#include "Core/Line2D.h"

namespace TikiEngine
{
	// default ctor
	Line2D::Line2D() 
		: normalCalculated(false)
	{
	}

	// default copy ctor
	Line2D::Line2D(const Line2D& Src)
		: normalCalculated(false)
	{
		*this = Src;
	}

	Line2D::Line2D(const Vector2& pA, const Vector2 pB)
	{
		pointA = pA;
		pointB = pB;
		normalCalculated = false;
	}

	// dtor
	Line2D::~Line2D()
	{
	}

	// operators
	Line2D& Line2D::operator=(const Line2D& src)
	{
		pointA = src.pointA;
		pointB = src.pointB;
		normal = src.normal;
		normalCalculated = src.normalCalculated;
		return (*this);
	}

	// setters
	void Line2D::SetEndPointA(const Vector2& p)
	{
		pointA = p;
		normalCalculated = false;
	}

	void Line2D::SetEndPointB(const Vector2& p)
	{
		pointB = p;
		normalCalculated = false;
	}

	const Vector2& Line2D::Normal() const
	{
		if (!normalCalculated)
			ComputeNormal();

		return normal;
	}

	void Line2D::SetPoints(const Vector2& pA, const Vector2& pB)
	{
		pointA = pA;
		pointB = pB;
		normalCalculated = false;
	}

	void Line2D::SetPoints(float pAx, float pAy, float pBx, float pBy)
	{
		pointA.X = pAx;
		pointA.Y = pAy;
		pointB.X = pBx;
		pointB.Y = pBy;
		normalCalculated = false;
	}

	float Line2D::SignedDistance(const Vector2& p) const
	{
		if (!normalCalculated)
			ComputeNormal();

		Vector2 testVector(p - pointA);
	
		return Vector2::Dot(testVector, normal);

	}

	Line2D::POINT_CLASSIFICATION Line2D::ClassifyPoint(const Vector2& p, float Epsilon) const
	{
		POINT_CLASSIFICATION res = ON_LINE;
		float distance = SignedDistance(p);
    
		if (distance > Epsilon)
			res = RIGHT_SIDE;
		else if (distance < -Epsilon)
			res = LEFT_SIDE;

		return res;
	}

    Line2D::LINE_CLASSIFICATION Line2D::Intersection(const Line2D& Line, Vector2* pIntersectPoint) const
	{
		float Ay_minus_Cy = pointA.Y - Line.EndPointA().Y;	
		float Dx_minus_Cx = Line.EndPointB().X - Line.EndPointA().X;	
		float Ax_minus_Cx = pointA.X - Line.EndPointA().X;	
		float Dy_minus_Cy = Line.EndPointB().Y - Line.EndPointA().Y;	
		float Bx_minus_Ax = pointB.X - pointA.X;	
		float By_minus_Ay = pointB.Y - pointA.Y;	

		float Numerator = (Ay_minus_Cy * Dx_minus_Cx) - (Ax_minus_Cx * Dy_minus_Cy);
		float Denominator = (Bx_minus_Ax * Dy_minus_Cy) - (By_minus_Ay * Dx_minus_Cx);

		// if lines do not intersect, return now
		if (!Denominator)
		{
			if (!Numerator)
				return COLLINEAR;

			return PARALLEL;
		}

		float FactorAB = Numerator / Denominator;
		float FactorCD = ((Ay_minus_Cy * Bx_minus_Ax) - (Ax_minus_Cx * By_minus_Ay)) / Denominator;

		// posting (hitting a vertex exactly) is not allowed, shift the results
		// if they are within a minute range of the end vertecies
		/*	if (fabs(FactorCD)  1.0e-6f)
			{
				FactorCD = 1.0e-6f;
			}
			if (fabs(FactorCD - 1.0f)  1.0e-6f)
			{
				FactorCD = 1.0f - 1.0e-6f;
			}
		*/

		// if an interection point was provided, fill it in now
		if (pIntersectPoint)
		{
			pIntersectPoint->X = (pointA.X + (FactorAB * Bx_minus_Ax));
			pIntersectPoint->Y = (pointA.Y + (FactorAB * By_minus_Ay));
		}

		// now determine the type of intersection
		if ((FactorAB >= 0.0f) && (FactorAB <= 1.0f) && 
			(FactorCD >= 0.0f) && (FactorCD <= 1.0f))
		{
			return SEGMENTS_INTERSECT;
		}
		else if ((FactorCD >= 0.0f) && (FactorCD <= 1.0f))
		{
			return (A_BISECTS_B);
		}
		else if ((FactorAB >= 0.0f) && (FactorAB <= 1.0f))
		{
			return (B_BISECTS_A);
		}

		return LINES_INTERSECT;
	}

	// accessors
	const Vector2& Line2D::EndPointA() const
	{
		return pointA;
	}
	
	const Vector2& Line2D::EndPointB() const
	{
		return pointB;
	}
	
	float Line2D::Length() const
	{
		float xdist = pointB.X - pointA.X;
		float ydist = pointB.Y - pointA.Y;
	
		xdist *= xdist;
		ydist *= ydist;
	
		return sqrtf(xdist + ydist);  // return static_cast<float>(sqrt(xdist + ydist));
	}

	void Line2D::GetDirection(Vector2& direction) const
	{
		direction = (pointB - pointA);
		direction.Normalize();
	}
	
	void Line2D::ComputeNormal() const
	{
		// Get Normailized direction from A to B
		GetDirection(normal);

		// Rotate by -90 degrees to get normal of line
		float oldYVal = normal.Y;
		normal.Y = -normal.X;
		normal.X = oldYVal;
		normalCalculated = true;

	}
}