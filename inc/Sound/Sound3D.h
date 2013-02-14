#pragma once

#include "Core/ISound3D.h"
#include "fmod/fmod.hpp"

namespace TikiEngine
{
	namespace Resources
	{
		class Sound3D : public ISound3D
		{
		public:

			Sound3D(Engine* engine);
			~Sound3D();

			void CreateInstance(ISound3D* obj);

			float GetDuration();

			void* GetNativeResource();
			bool GetReady();
		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			char* data;
		};
	}
}