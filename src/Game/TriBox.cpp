#include "Game/TriBox.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace AI
	{
		// This Triangle-Box intersection code was adapated from the Graphics Gems III
		// source archive 'triangleCube.c' available at: http://www.acm.org/tog/GraphicsGems/
		// The main modification is that the original code performed only intersection
		// with a voxel (that is, a unit cube centered at the origin).  This code is
		// modified to take an arbitrary box and triangle and perform the scale/translation
		// necessary to get the triangle into voxel space.


		// Which of the six face-plane(s) is point P outside of? 
		static int FacePlane(Vector3 p)
		{
			int outcode = 0;
			if (p.X >  .5) outcode |= 0x01;
			if (p.X < -.5) outcode |= 0x02;
			if (p.Y >  .5) outcode |= 0x04;
			if (p.Y < -.5) outcode |= 0x08;
			if (p.Z >  .5) outcode |= 0x10;
			if (p.Z < -.5) outcode |= 0x20;
			return outcode;
		}

		// Which of the twelve edge plane(s) is point P outside of?
		static int Bevel2d(Vector3 p)
		{
			int outcode = 0;
			if ( p.X + p.Y > 1.0) outcode |= 0x001;
			if ( p.X - p.Y > 1.0) outcode |= 0x002;
			if (-p.X + p.Y > 1.0) outcode |= 0x004;
			if (-p.X - p.Y > 1.0) outcode |= 0x008;
			if ( p.X + p.Z > 1.0) outcode |= 0x010;
			if ( p.X - p.Z > 1.0) outcode |= 0x020;
			if (-p.X + p.Z > 1.0) outcode |= 0x040;
			if (-p.X - p.Z > 1.0) outcode |= 0x080;
			if ( p.Y + p.Z > 1.0) outcode |= 0x100;
			if ( p.Y - p.Z > 1.0) outcode |= 0x200;
			if (-p.Y + p.Z > 1.0) outcode |= 0x400;
			if (-p.Y - p.Z > 1.0) outcode |= 0x800;
			return outcode;
		}

		// Which of the eight corner plane(s) is point P outside of? 
		static int Bevel3d(Vector3 p)
		{
			int outcode = 0;
			if (( p.X + p.Y + p.Z) > 1.5) outcode |= 0x01;
			if (( p.X + p.Y - p.Z) > 1.5) outcode |= 0x02;
			if (( p.X - p.Y + p.Z) > 1.5) outcode |= 0x04;
			if (( p.X - p.Y - p.Z) > 1.5) outcode |= 0x08;
			if ((-p.X + p.Y + p.Z) > 1.5) outcode |= 0x10;
			if ((-p.X + p.Y - p.Z) > 1.5) outcode |= 0x20;
			if ((-p.X - p.Y + p.Z) > 1.5) outcode |= 0x40;
			if ((-p.X - p.Y - p.Z) > 1.5) outcode |= 0x80;
			return outcode;
		}

		// Test the point "alpha" of the way from p1 to p2 and check if it is on a face of the cube.
		// Consider only faces in "mask"
		static int CheckPoint(Vector3 p1, Vector3 p2, float alpha, long mask)
		{
			Vector3 planePoint;
			planePoint.X = LERP(alpha, p1.X, p2.X);
			planePoint.Y = LERP(alpha, p1.Y, p2.Y);
			planePoint.Z = LERP(alpha, p1.Z, p2.Z);
			return (FacePlane(planePoint) & mask);
		}

		// Compute intersection of P1 --> P2 line segment with face planes 
		// Then test intersection point to see if it is on cube face       
		// Consider only face planes in "outcode_diff"                     
		// Note: Zero bits in "outcodeDiff" means face line is outside of
		static int CheckLine(Vector3 p1, Vector3 p2, int outcodeDiff)
		{
			if ((0x01 & outcodeDiff) != 0)
				if (CheckPoint(p1,p2,( .5f-p1.X)/(p2.X-p1.X),0x3e) == INSIDE) 
					return INSIDE;

			if ((0x02 & outcodeDiff) != 0)
				if (CheckPoint(p1,p2,(-.5f-p1.X)/(p2.X-p1.X),0x3d) == INSIDE)
					return INSIDE;

			if ((0x04 & outcodeDiff) != 0) 
				if (CheckPoint(p1,p2,( .5f-p1.Y)/(p2.Y-p1.Y),0x3b) == INSIDE) 
					return INSIDE;

			if ((0x08 & outcodeDiff) != 0) 
				if (CheckPoint(p1,p2,(-.5f-p1.Y)/(p2.Y-p1.Y),0x37) == INSIDE) 
					return INSIDE;

			if ((0x10 & outcodeDiff) != 0) 
				if (CheckPoint(p1,p2,( .5f-p1.Z)/(p2.Z-p1.Z),0x2f) == INSIDE) 
					return INSIDE;
			if ((0x20 & outcodeDiff) != 0) 
				if (CheckPoint(p1,p2,(-.5f-p1.Z)/(p2.Z-p1.Z),0x1f) == INSIDE) 
					return INSIDE;

			return OUTSIDE;
		}

		// Test if 3D point is inside 3D triangle 
		static int PointTriangleIntersection(Vector3 p, TRI t)
		{
			int		sign12, sign23, sign31;
			Vector3 vect12, vect23, vect31, vect1h, vect2h, vect3h;
			Vector3 cross12_1p, cross23_2p, cross31_3p;

			//	First, a quick bounding-box test:                               
			//  If P is outside triangle bbox, there cannot be an intersection. 
			if (p.X > Max3(t.Pt[0].X, t.Pt[1].X, t.Pt[2].X)) return OUTSIDE;  
			if (p.Y > Max3(t.Pt[0].Y, t.Pt[1].Y, t.Pt[2].Y)) return OUTSIDE;
			if (p.Z > Max3(t.Pt[0].Z, t.Pt[1].Z, t.Pt[2].Z)) return OUTSIDE;
			if (p.X < Min3(t.Pt[0].X, t.Pt[1].X, t.Pt[2].X)) return OUTSIDE;
			if (p.Y < Min3(t.Pt[0].Y, t.Pt[1].Y, t.Pt[2].Y)) return OUTSIDE;
			if (p.Z < Min3(t.Pt[0].Z, t.Pt[1].Z, t.Pt[2].Z)) return OUTSIDE;

			//	For each triangle side, make a vector out of it by subtracting vertexes; 
			//	make another vector from one vertex to point P.                          
			//  The crossproduct of these two vectors is orthogonal to both and the      
			//  signs of its X,Y,Z components indicate whether P was to the inside or    
			//  to the outside of this triangle side.    
			vect12 = t.Pt[0] - t.Pt[1];
			vect1h = t.Pt[0] - p;	
			cross12_1p = Vector3::Cross(vect12, vect1h);
			sign12 = Sign3(cross12_1p);      

			vect23 = t.Pt[1] - t.Pt[2];
			vect2h = t.Pt[1] - p;
			cross23_2p = Vector3::Cross(vect23, vect2h);
			sign23 = Sign3(cross23_2p);

			vect31 = t.Pt[2] - t.Pt[0];
			vect3h = t.Pt[2] - p;
			cross31_3p = Vector3::Cross(vect31, vect3h);
			sign31 = Sign3(cross31_3p);

			//	If all three crossproduct vectors agree in their component signs, 
			//  then the point must be inside all three.                           
			//  P cannot be OUTSIDE all three sides simultaneously.    
			return ( ( (sign12 & sign23 & sign31) == 0) ? OUTSIDE : INSIDE );
		}


		// Triangle t is compared with a unit cube, centered on the origin.                    
		// It returns INSIDE (0) or OUTSIDE(1) if t	Intersects or does not intersect the cube. 
		static int TriCubeIntersection(TRI t)
		{
			int v1_test, v2_test, v3_test;
			float d;
			Vector3 vect12, vect13, norm;
			Vector3 hitpp, hitpn, hitnp, hitnn;

			//	First compare all three vertexes with all six face-planes 
			//	If any vertex is inside the cube, return immediately!    
			if ((v1_test = FacePlane(t.Pt[0])) == INSIDE) return INSIDE;
			if ((v2_test = FacePlane(t.Pt[1])) == INSIDE) return INSIDE;
			if ((v3_test = FacePlane(t.Pt[2])) == INSIDE) return INSIDE;

			//	If all three vertexes were outside of one or more face-planes,
			//	return immediately with a trivial rejection!   
			if ((v1_test & v2_test & v3_test) != 0) 
				return OUTSIDE;

			//	Now do the same trivial rejection test for the 12 edge planes 
			v1_test |= Bevel2d(t.Pt[0]) << 8; 
			v2_test |= Bevel2d(t.Pt[1]) << 8; 
			v3_test |= Bevel2d(t.Pt[2]) << 8;
			if ((v1_test & v2_test & v3_test) != 0) 
				return OUTSIDE;  

			//	Now do the same trivial rejection test for the 8 corner planes
			v1_test |= Bevel3d(t.Pt[0]) << 24; 
			v2_test |= Bevel3d(t.Pt[1]) << 24; 
			v3_test |= Bevel3d(t.Pt[2]) << 24; 
			if ((v1_test & v2_test & v3_test) != 0) 
				return(OUTSIDE);   

			// If vertex 1 and 2, as a pair, cannot be trivially rejected 
			// by the above tests, then see if the v1-->v2 triangle edge  
			// intersects the cube.  Do the same for v1-->v3 and v2-->v3. 
			// Pass to the intersection algorithm the "OR" of the outcode 
			// bits, so that only those cube faces which are spanned by   
			// each triangle edge need be tested.     
			if ((v1_test & v2_test) == 0)
				if (CheckLine(t.Pt[0], t.Pt[1], v1_test | v2_test) == INSIDE) return(INSIDE);
			if ((v1_test & v3_test) == 0)
				if (CheckLine(t.Pt[0], t.Pt[2], v1_test | v3_test) == INSIDE) return(INSIDE);
			if ((v2_test & v3_test) == 0)
				if (CheckLine(t.Pt[1], t.Pt[2], v2_test | v3_test) == INSIDE) return(INSIDE);

			//	By now, we know that the triangle is not off to any side,     
			//	and that its sides do not penetrate the cube.  We must now   
			//	test for the cube intersecting the interior of the triangle. 
			//	We do this by looking for intersections between the cube     
			//	diagonals and the triangle...first finding the intersection  
			//	of the four diagonals with the plane of the triangle, and    
			//	then if that intersection is inside the cube, pursuing       
			//	whether the intersection point is inside the triangle itself. 

			//	To find plane of the triangle, first perform crossproduct on  
			//	two triangle side vectors to compute the normal vector.      
			vect12 = t.Pt[0] - t.Pt[1];
			vect13 = t.Pt[0] - t.Pt[2];
			norm = Vector3::Cross(vect12, vect13);

			// The normal vector "norm" X,Y,Z components are the coefficients 
			// of the triangles AX + BY + CZ + D = 0 plane equation.  If we   
			// solve the plane equation for X=Y=Z (a diagonal), we get        
			// -D/(A+B+C) as a metric of the distance from cube center to the 
			// diagonal/plane intersection.  If this is between -0.5 and 0.5, 
			// the intersection is inside the cube.  If so, we continue by    
			// doing a point/triangle intersection.                           
			// Do this for all four diagonals.    
			d = norm.X * t.Pt[0].X + norm.Y * t.Pt[0].Y + norm.Z * t.Pt[0].Z;
			hitpp.X = hitpp.Y = hitpp.Z = d / (norm.X + norm.Y + norm.Z);
			if (fabs(hitpp.X) <= 0.5)
				if (PointTriangleIntersection(hitpp, t) == INSIDE) 
					return(INSIDE);

			hitpn.Z = -(hitpn.X = hitpn.Y = d / (norm.X + norm.Y - norm.Z));
			if (fabs(hitpn.X) <= 0.5)
				if (PointTriangleIntersection(hitpn, t) == INSIDE) 
					return(INSIDE);

			hitnp.Y = -(hitnp.X = hitnp.Z = d / (norm.X - norm.Y + norm.Z));
			if (fabs(hitnp.X) <= 0.5)
				if (PointTriangleIntersection(hitnp, t) == INSIDE) 
					return(INSIDE);

			hitnn.Y = hitnn.Z = -(hitnn.X = d / (norm.X - norm.Y - norm.Z));
			if (fabs(hitnn.X) <= 0.5)
				if (PointTriangleIntersection(hitnn, t) == INSIDE) 
					return(INSIDE);

			//	No edge touched the cube; no cube diagonal touched the triangle. 
			//  We're done...there was no intersection.        
			return OUTSIDE;
		}


		int TriBoxIntersect(IBoundingBox* box, TRI tri)
		{
			Vector3 trans;
			Vector3 transMax;
			Vector3 scale;
			TRI testTri;

			// Compute the scale and transofrm required to make box a Voxel
			trans = (box->GetMax() + box->GetMin()) / 2;
			transMax = box->GetMax() - trans;

			if (transMax.X != 0)
				scale.X = 0.5f / transMax.X;
			if (transMax.Y != 0)
				scale.Y = 0.5f / transMax.Y;
			if (transMax.Z != 0)
				scale.Z = 0.5f / transMax.Z;


			// put the triangle in voxel space
			for (int i = 0; i < 3; i++)
			{
				testTri.Pt[i].X = (tri.Pt[i].X - trans.X) * scale.X;
				testTri.Pt[i].Y = (tri.Pt[i].Y - trans.Y) * scale.Y;
				testTri.Pt[i].Z = (tri.Pt[i].Z - trans.Z) * scale.Z;
			}

			// Test triangle against voxel
			return TriCubeIntersection(testTri);
		}

	}
}