
#include "Graphics/Model.h"

namespace TikiEngine
{
	namespace Resources
	{
#pragma region Class
		Model::Model(Engine* engine)
			: IModel(engine)
		{
		}

		Model::~Model()
		{

		}
#pragma endregion



#pragma region Member

		void* Model::GetNativeResource()
		{
			return NULL;
		}

		bool Model::GetReady()
		{
			return true;//(texture != 0);
		}
#pragma endregion


#pragma region Protected Member - Load/Save
		void Model::loadFromStream(wcstring fileName, Stream* stream)
		{

		}

		void Model::saveToStream(wcstring fileName, Stream* stream)
		{

		}
#pragma endregion
	}
}
