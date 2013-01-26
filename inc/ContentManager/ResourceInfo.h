#pragma once

#include "Core/TypeInc.h"
#include "Core/IResource.h"

namespace TikiEngine
{
	using TikiEngine::Resources::IResource;

	struct ResourceInfo
	{
		ResourceInfo() : hash(0), fileName(), resource(0) {}
		ResourceInfo(PInt hash, wstring name, IResource* res) : hash(hash), fileName(name), resource(res) {}

		~ResourceInfo() { }

		PInt hash;
		wstring fileName;
		IResource* resource;
	};
}