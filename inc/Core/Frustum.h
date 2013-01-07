#pragma once

#include "Core/Plane.h"
#include "Core/IBoundingBox.h"
#include "Core/Frustum.h"
#include "Core/RectangleF.h"
#include "Core/IGraphics.h"

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

		void CreatePlanes(const Matrix& m)
		{
			pl[LEFT].SetParameter(-m.M14 - m.M11, -m.M24 - m.M21,
				-m.M34 - m.M31, -m.M44 - m.M41);

			pl[RIGHT].SetParameter(m.M11 - m.M14, m.M21 - m.M24,
				m.M31 - m.M34, m.M41 - m.M44);

			pl[TOP].SetParameter(m.M12 - m.M14, m.M22 - m.M24,
				m.M32 - m.M34, m.M42 - m.M44);

			pl[BOTTOM].SetParameter(-m.M14 - m.M12, -m.M24 - m.M22,
				-m.M34 - m.M32, -m.M44 - m.M42);

			pl[NEARP].SetParameter(-m.M13, -m.M23, -m.M33, -m.M43);

			pl[FARP].SetParameter(m.M13 - m.M14, m.M23 - m.M24,
				m.M33 - m.M34, m.M43 - m.M44);
		}

		void Draw(const DrawArgs& args)
		{
			float scale = 0.1f;

			Vector3 v1 = IntersectionPoint(pl[NEARP], pl[LEFT], pl[TOP]) * scale;
			Vector3 v2 = IntersectionPoint(pl[NEARP], pl[RIGHT], pl[TOP]) * scale;
			Vector3 v3 = IntersectionPoint(pl[NEARP], pl[RIGHT], pl[BOTTOM]) * scale;
			Vector3 v4 = IntersectionPoint(pl[NEARP], pl[LEFT], pl[BOTTOM]) * scale;
			Vector3 v5 = IntersectionPoint(pl[FARP], pl[LEFT], pl[TOP]) * scale;
			Vector3 v6 = IntersectionPoint(pl[FARP], pl[RIGHT], pl[TOP]) * scale;
			Vector3 v7 = IntersectionPoint(pl[FARP], pl[RIGHT], pl[BOTTOM]) * scale;
			Vector3 v8 = IntersectionPoint(pl[FARP], pl[LEFT], pl[BOTTOM]) * scale;

			args.Graphics->DrawLine(v1, v2, Color::Red);
			args.Graphics->DrawLine(v2, v3, Color::Red);
			args.Graphics->DrawLine(v3, v4, Color::Red);
			args.Graphics->DrawLine(v4, v1, Color::Red);

			args.Graphics->DrawLine(v5, v6, Color::Green);
			args.Graphics->DrawLine(v6, v7, Color::Green);
			args.Graphics->DrawLine(v7, v8, Color::Green);
			args.Graphics->DrawLine(v8, v5, Color::Green);

			args.Graphics->DrawLine(v5 / scale, v6 / scale, Color::Red); //oben
			args.Graphics->DrawLine(v6 / scale, v7 / scale, Color::Green); //rechts
			args.Graphics->DrawLine(v7 / scale, v8 / scale, Color::Blue); //unten
			args.Graphics->DrawLine(v8 / scale, v5 / scale, Color::Black); // links


			args.Graphics->DrawLine(v1, v5, Color::Blue);
			args.Graphics->DrawLine(v2, v6, Color::Blue);
			args.Graphics->DrawLine(v3, v7, Color::Blue);
			args.Graphics->DrawLine(v4, v8, Color::Blue);

		}

		Vector3 IntersectionPoint(Plane& a, Plane& b, Plane& c)
		{
			Vector3 v1, v2, v3;
			float f = -Vector3::Dot(a.Normal(), Vector3::Cross(b.Normal(), c.Normal()));

			v1 = ((Vector3::Cross(b.Normal(), c.Normal())) * a.Distance());
			v2 = ((Vector3::Cross(c.Normal(), a.Normal())) * b.Distance());
			v3 = ((Vector3::Cross(a.Normal(), b.Normal())) * c.Distance());

			Vector3 vec = Vector3(v1.X + v2.X + v3.X, v1.Y + v2.Y + v3.Y, v1.Z + v2.Z + v3.Z);
			return vec / f;

		}

		int PointInFrustum(const Vector3& p)
		{
			for(int i=0; i < 6; i++) 
			{
				if(ClassifyPoint(pl[i], p) > 0)
					return OUTSIDE;
			}
			return INSIDE;

			//int result = INSIDE;
			//for(int i=0; i < 6; i++) {

			//	if (pl[i].Distance(p) < 0)
			//		return OUTSIDE;
			//}
			//return(result);
		}

		int SphereInFrustum(const Vector3& p, float radius)
		{
			_CrtDbgBreak(); //NYI
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
			_CrtDbgBreak(); //NYI
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

		inline int RectangleInFrustum(RectangleF& rect, float height = 0)
		{

			_CrtDbgBreak(); //NYI
			int result = INSIDE;
			for(int i = 0; i < 6; i++) 
			{
				if (pl[i].Distance(rect.GetVertexP(pl[i].Normal(), height)) < 0)
					return OUTSIDE;
				else if (pl[i].Distance(rect.GetVertexN(pl[i].Normal(), height)) < 0)
					result = INTERSECT;
			}
			return(result);
		}

		private:

			inline float ClassifyPoint(const Plane& plane, const Vector3& point)
			{
				return point.X * plane.Normal().X + point.Y * plane.Normal().Y + point.Z * plane.Normal().Z + plane.Distance();
			}
	};




}

