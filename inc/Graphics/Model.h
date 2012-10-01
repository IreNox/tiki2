#pragma once

#include "Core/IModel.h"


namespace TikiEngine
{
	namespace Resources
	{
		class Model : public IModel
		{
		public:

			Model(Engine* engine);
			~Model();

			void* GetNativeResource();

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

		};
	}
}