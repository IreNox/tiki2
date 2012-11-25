#pragma once

#include "Core/TypeInc.h"

namespace TikiEngine
{
	namespace Resources
	{
		enum PartType
		{
			PT_Mesh,
			PT_Bone,
			PT_Layer,
			PT_Animation,
			PT_String,
			PT_Array,
			PT_NoArray,
			PT_Byte,
			PT_UInt,
			PT_Double,
			PT_Vector3,
			PT_Quaternion
		};

		struct BinaryFileHeader
		{
			char TIKI[4];

			UInt32 FileLength;
			UInt32 PartCount;

			UInt32 RootBoneId;

			UInt32 MeshArrayId;
			UInt32 AnimationArrayId;
		};

		struct BinaryPart
		{
			UInt32 Id;

			PartType Type;
			PartType ArrayOf;
			UInt32 ArrayCount;

			UInt32 Start;
			UInt32 Length;
		};

		struct BinaryTikiAnimation
		{
			UInt32 NameId;
			UInt32 TimeStampsArrayId;
			UInt32 BSV;
			UInt32 Temp;

			double StartTime;
			double EndTime;
		};

		struct BinaryTikiBone
		{
			UInt32 NameId;

			UInt32 ParentId;
			UInt32 ChildsArrayId;
			UInt32 LayerArrayId;

			Matrix Init;

			Int32 ConstanBufferIndex;
		};

		struct BinaryTikiLayer
		{
			UInt32 AnimationId;

			UInt32 TranslationArrayId;
			UInt32 RotationArrayId;
		};

		struct BinaryTikiMesh 
		{
			UInt32 NameId;

			UInt32 VertexDataId;
			UInt32 IndexDataId;

			Boolean UseDeformation;

			UInt32 DiffuseTexId;
			UInt32 NormalTexId;
			UInt32 SpecTexId;
			UInt32 LightTexId;
		};
	}
}