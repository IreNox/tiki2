#pragma once

#include "Core/Vector2.h"

namespace TikiEngine
{
	/* Represents a line in 2D space. Line data is held as a line segment having two 
	 * endpoints and as a fictional 3D plane extending verticaly. The Plane is then used for
	 * spanning and point clasification tests. A Normal vector is used internally to represent
	 * the fictional plane.
	 */
	class Line2D
	{
	public:
		// enums
		enum POINT_CLASSIFICATION
		{
			ON_LINE,	// The point is on, or very near, the line
			LEFT_SIDE,  // looking from endpoint A to B, the test point is on the left
			RIGHT_SIDE  // looking from endpoint A to B, the test point is on the right
		};

		enum LINE_CLASSIFICATION
		{
			COLLINEAR,			// both lines are parallel and overlap each other
			LINES_INTERSECT,    // lines intersect, but their segments do not
			SEGMENTS_INTERSECT, // both line segments bisect each other
			A_BISECTS_B,		// line segment B is crossed by line A
			B_BISECTS_A,		// line segment A is crossed by line B
			PARALLEL			// the lines are parallel
		};

		// ctor / dtor
		Line2D();
		Line2D(const Line2D& src);
		Line2D(const Vector2& pA, const Vector2 pB);
		~Line2D();

		// operators
		Line2D& operator=(const Line2D& src);

		// setters / getters
		void SetEndPointA(const Vector2& p);
		void SetEndPointB(const Vector2& p);
		void SetPoints(const Vector2& pA, const Vector2& pB);
		void SetPoints(float pAx, float pAy, float pBx, float pBy);
	
		// Determines the signed distance from a point to this line. Consider the line as
		// if you were standing on PointA of the line looking towards PointB. Posative distances
		// are to the right of the line, negative distances are to the left.
		float SignedDistance(const Vector2& p) const;

		// Determines where a point lies in relation to this line. Consider the line as
		// if you were standing on PointA of the line looking towards PointB. The incomming
		// point is then classified as being on the Left, Right or Centered on the line.
		POINT_CLASSIFICATION ClassifyPoint(const Vector2& p, float Epsilon = 0.0f) const;

		// Determines if two segments intersect, and if so the point of intersection. The current
		// member line is considered line AB and the incomming parameter is considered line CD for
		// the purpose of the utilized equations.
		// A = PointA of the member line
		// B = PointB of the member line
		// C = PointA of the provided line	
		// D = PointB of the provided line	
		LINE_CLASSIFICATION Intersection(const Line2D& Line, Vector2* pIntersectPoint = 0) const;

		void GetDirection(Vector2& direction) const;

		// accessprs
		const Vector2& EndPointA()const;
		const Vector2& EndPointB()const;
		const Vector2& Normal()const;
		float Length() const;

	private:
		void ComputeNormal() const;

		Vector2 pointA;		// Endpoint A of our line segment
		Vector2 pointB;		// Endpoint B of our line segment

		mutable Vector2 normal;	// normal of the Ray: a vector pointing to the right-hand side of the line when viewed from PointA towards PointB
		mutable bool normalCalculated; // normals are only calculated on demand
	};


}