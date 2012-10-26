
#include "Game/BoxSide.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace AI
	{
		// Normals for each box side
		const float SideNormals[6][3]= 
		{
			{  0.0,  1.0,  0.0 }, // Top
			{  0.0, -1.0,  0.0 }, // Bottom
			{  1.0,  0.0,  0.0 }, // Right
			{ -1.0,  0.0,  0.0 }, // Left
			{  0.0,  0.0,  1.0 }, // Front
			{  0.0,  0.0, -1.0 } // Back
		};


		const int PT_MIN = 0;
		const int PT_MAX = 1;

		// Types of points for each vert of the box relative to the Min/Max
		const int PtTypes[8][3]=
		{
			{ PT_MIN, PT_MIN, PT_MIN },
			{ PT_MAX, PT_MIN, PT_MIN },
			{ PT_MAX, PT_MIN, PT_MAX },
			{ PT_MIN, PT_MIN, PT_MAX },
			{ PT_MIN, PT_MAX, PT_MIN },
			{ PT_MAX, PT_MAX, PT_MIN },
			{ PT_MAX, PT_MAX, PT_MAX },
			{ PT_MIN, PT_MAX, PT_MAX }
		};

		// Indices of points for each box face
		const int PtIndices[6][4]=
		{
			{ 7, 6, 5, 4 }, // Top
			{ 0, 1, 2, 3 }, // Bottom
			{ 5, 6, 2, 1 }, // Right
			{ 0, 3, 7, 4 }, // Left
			{ 7, 6, 2, 3 }, // Front
			{ 0, 1, 5, 4 } // Back
		};

		BoxSide::BoxSide()
		{
		}

		BoxSide::~BoxSide()
		{
		}

		Vector3 BoxSide::GetBoxPt(IBoundingBox* box, int index)
		{
			Vector3 pt;

			for(int i = 0; i < 3; i++)
			{
				if (PtTypes[index][i] == PT_MIN)
					pt.arr[i] = box->GetMin().arr[i];
				else
					pt.arr[i] = box->GetMax().arr[i];
			}

			return pt;
		}

		int BoxSide::CoPlanar(BoxSide testSide)
		{
			//	Check to see if all points satisfy plane equation for TestSide: Ax + By + Cz + D = 0
			for(int i = 0; i < 4; i++)
			{
				float result = testSide.Normal.X * Points[i].X + 
							   testSide.Normal.Y * Points[i].Y + 
							   testSide.Normal.Z * Points[i].Z +
							   testSide.D;

				if(!ApproxEqual(result, 0))
					return 0;
			}

			return 1;
		}

		int BoxSide::PointsInside(BoxSide testSide)
		{
			for(int i = 0; i < 4; i++)
			{
				int lessEq = 0;
				int greaterEq = 0;

				for(int j = 0; j < 4 || (!lessEq && !greaterEq); j++)
				{
					if(Points[i].X >= testSide.Points[j].X)
						if(Points[i].Y >= testSide.Points[j].Y)
							if(Points[i].Z >= testSide.Points[j].Z)
								greaterEq = 1;

					if(Points[i].X <= testSide.Points[j].X)
						if(Points[i].Y <= testSide.Points[j].Y)
							if(Points[i].Z <= testSide.Points[j].Z)
								lessEq = 1;
				}

				if(!lessEq || !greaterEq)
					return 0;
			}

			return 1;
		}

		void BoxSide::SetFromBox(IBoundingBox* box, int side)
		{
			if (side >= 0 && side <= 5)
			{
				Normal.X = SideNormals[side][0];
				Normal.Y = SideNormals[side][1];
				Normal.Z = SideNormals[side][2];

				for (int i = 0; i < 4; i++)
					Points[i] = GetBoxPt(box, PtIndices[side][i]);

				D = -(Points[0].X * Normal.X + 
					  Points[0].Y * Normal.Y + 
					  Points[0].Z * Normal.Z );

				Size = box->GetMax().X - box->GetMin().X;
				CurSide = side;
			}
		}

		int BoxSide::Neighbors(BoxSide TestSide)
		{
			//	planes don't face each other
			if((CurSide % 2)== (TestSide.CurSide % 2))
				return 0;

			//	Check to see if planes are coplanar
			if(CoPlanar(TestSide))
				if(PointsInside(TestSide))
					return 1;

			return 0;
		}

		float BoxSide::GetSize()
		{
			return Size;
		}

	}
}