#pragma once

namespace TikiEditor
{
	struct BinaryTikiMesh 
	{
		UInt32 NameId;

		UInt32 VertexDataId;
		UInt32 IndexDataId;

		bool UseDeformation;

		UInt32 DiffuseTexId;
		UInt32 NormalTexId;
		UInt32 SpecTexId;
		UInt32 LightTexId;
	};
}