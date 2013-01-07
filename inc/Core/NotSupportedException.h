#pragma once

#include "Core/Exception.h"

namespace TikiEngine
{
	class NotSupportedException : public Exception
	{
	public:
		NotSupportedException()
			: Exception("This method is not supported")
		{
		}
	};
}