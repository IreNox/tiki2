#pragma once

#include "Core/Plane.h"
#include "Core/IBoundingBox.h"
#include "Core/Frustum.h"
#include "Core/RectangleF.h"

namespace TikiEngine
{
	using namespace TikiEngine::Resources;

	class Frustum
	{

	private:
		enum 
		{
			TOP = 0,
			BOTTOM,
			LEFT,
			RIGHT,
			NEARP,
			FARP
		};

	public:
		static enum {OUTSIDE, INTERSECT, INSIDE};

		// The planes
		Plane pl[6];

		Frustum(){}
		~Frustum(){}


		// performs the plane extraction assuming that the matriz m = View * Projection 
		void Set(const Matrix& m)
		{
				pl[NEARP].SetCoeff(m.M13 + m.M14,  
								   m.M23 + m.M24,  
								   m.M33 + m.M34,  
								   m.M43 + m.M44); 	   
										   
				pl[FARP].SetCoeff(-m.M13 + m.M14,  
								  -m.M23 + m.M24,  
								  -m.M33 + m.M34,  
								  -m.M43 + m.M44); 

				pl[BOTTOM].SetCoeff(m.M12 + m.M14,	
									m.M22 + m.M24, 
									m.M32 + m.M34, 
									m.M42 + m.M44);
 
				pl[TOP].SetCoeff(-m.M12 + m.M14,  
								 -m.M22 + m.M24,  
								 -m.M32 + m.M34,  
								 -m.M42 + m.M44); 

				pl[LEFT].SetCoeff(m.M11 + m.M14,	
								  m.M21 + m.M24,	
								  m.M31 + m.M34,	
								  m.M41 + m.M44);	

				pl[RIGHT].SetCoeff(-m.M11 + m.M14,	
								   -m.M21 + m.M24,	
								   -m.M31 + m.M34,	
								   -m.M41 + m.M44);	
		}

		int PointInFrustum(const Vector3& p)
		{
			int result = INSIDE;
			for(int i=0; i < 6; i++) {

				if (pl[i].Distance(p) < 0)
					return OUTSIDE;
			}
			return(result);
		}

		int SphereInFrustum(const Vector3& p, float radius)
		{
			int result = INSIDE;
			float distance;

			for(int i = 0; i < 6; i++) 
			{
				distance = pl[i].Distance(p);
				if (distance < -radius)
					return OUTSIDE;
				else if (distance < radius)
					result = INTERSECT;
			}
			return(result);
		}

		int BoxInFrustum(IBoundingBox* b)
		{
			int result = INSIDE;
			for(int i = 0; i < 6; i++) 
			{
				if (pl[i].Distance(b->GetVertexP(pl[i].Normal())) < 0)
					return OUTSIDE;
				else if (pl[i].Distance(b->GetVertexN(pl[i].Normal())) < 0)
					result = INTERSECT;
			}
			return(result);
		}

		inline bool RectangleInFrustum(RectangleF& rect, float height = 0)
		{
			if(PointInFrustum(rect.TopLeft(height)) == INSIDE
			&& PointInFrustum(rect.TopRight(height)) == INSIDE
			&& PointInFrustum(rect.BottomLeft(height)) == INSIDE
			&& PointInFrustum(rect.BottomRight(height)) == INSIDE)
				return true;

			return false;

		}
	};




}

