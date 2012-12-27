#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	template <typename T>
	class TikiEnum
	{
	public:

		#pragma region Class
		TikiEnum(T value)
			: value(value)
		{
		}

		~TikiEnum()
		{
		}
		#pragma endregion

		#pragma region Member
		inline T GetValue() { return value; }
		inline T& SetValue() { return value; }

		inline void SetFlag(T flag) { value |= flag; }
		inline void RemoveFlag(T flag) { value ^= flag; }

		inline bool HasFlag(T flag) { return (value & flag) != 0; }
		#pragma endregion

	private:

		T value;

	};
}