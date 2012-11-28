#pragma  once

#include "Core/IResource.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IBone : public IResource
		{
		public:
			IBone() : IResource(0){}
			virtual ~IBone(){}

			virtual void* GetNativeResource() 
			{
				return 0;
			}
			virtual bool GetReady()
			{
				return true;
			}

		protected:

			void loadFromStream(wcstring fileName, Stream* stream)
			{

			}
			void saveToStream(wcstring fileName, Stream* stream)
			{

			}
		};
	}
}