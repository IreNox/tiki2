#pragma once

#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	template <class T>
	class TikiPtr
	{
	public:

		TikiPtr()
			: ptr(0)
		{
		}

		TikiPtr(T* pPtr)
			: ptr(pPtr)
		{
		}

		~TikiPtr()
		{
			SafeRelease(&ptr);
		}

		bool operator==(T* rhs)
		{
			return (ptr == rhs);
		}

		T* operator=()
		{

		}

	private:

		T* ptr;

	};
}