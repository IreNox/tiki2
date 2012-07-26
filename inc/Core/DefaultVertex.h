#pragma once

#include <D3D11.h>

#include "Core/Vector2.h"
#include "Core/Vector3.h"
#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct DefaultVertex
		{
			float Position[3];
			float Normal[3];
			float UV[2];

			//DefaultVertex(const Vector3& pos, const Vector3& normal, const Vector2& uv)
			//{
			//	this->Position[0] = pos.X;
			//	this->Position[1] = pos.Y;
			//	this->Position[2] = pos.Z;

			//	this->Normal[0] = normal.X;
			//	this->Normal[1] = normal.Y;
			//	this->Normal[2] = normal.Z;

			//	this->UV[0] = uv.X;
			//	this->UV[1] = uv.Y;
			//}
		};

		class DefaultVertexDeclaration : public VertexDeclaration
		{
		public:
			DefaultVertexDeclaration(TikiEngine::Engine* engine, Shader* shader);
			~DefaultVertexDeclaration();

		};
	}
}