#pragma once

using System::String;

namespace TikiEditor
{
	public ref class MeshMaterial
	{
	public:

		MeshMaterial() {}
		~MeshMaterial() {}

		property String^ Name
		{
			String^ get() { return name; }
			void set(String^ value) { name = value; }
		}

		property System::Boolean CreatetAdjacencyIndices
		{
			System::Boolean get() { return createtAdjacencyIndices; }
			void set(System::Boolean value) { createtAdjacencyIndices = value; }
		}

		property String^ TextureDiffuse
		{
			String^ get() { return texDiffuse; }
			void set(String^ value) { texDiffuse = value; }
		}

		property String^ TextureNormal
		{
			String^ get() { return texNormal; }
			void set(String^ value) { texNormal = value; }
		}

		property String^ TextureSpec
		{
			String^ get() { return texSpec; }
			void set(String^ value) { texSpec = value; }
		}

		property String^ TextureLight
		{
			String^ get() { return texLight; }
			void set(String^ value) { texLight = value; }
		}

	private:

		String^ name;

		bool createtAdjacencyIndices;

		String^ texDiffuse;
		String^ texNormal;
		String^ texSpec;
		String^ texLight;

	};
}