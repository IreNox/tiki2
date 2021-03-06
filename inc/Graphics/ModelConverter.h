#pragma once

#include "Core/TypeDef.h"

#if defined TIKI_ENGINE
#include "Graphics/Model.h"
#elif defined TIKI_EDITOR
#include "ModelEditor.h"
#endif 

#include "Graphics/ModelIOContext.h"
#include "Graphics/ModelBinaryData.h"

#include "Core/List.h"
#include "Core/Stream.h"

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::IO;

		class ModelConverter
		{
		public:

			ModelConverter(Model* model);
			ModelConverter(Model* model, Stream* stream);
			~ModelConverter();

			Model* GetModel();
			void WriteToStream(Stream* stream);

		private:

			Model* model;
			ModelIOContext* context;

			List<UInt32> meshIds;
			List<UInt32> animationIds;
			List<TikiBone*> constantBufferIndices;

			void readPartsModel();
			TikiMesh* readTikiMesh(BinaryPart& part, BinaryTikiMesh* binMesh);
			TikiBone* readTikiBone(BinaryPart& part, BinaryTikiBone* binBone, TikiBone* parent);
			TikiAnimation* readTikiAnimation(BinaryPart& part, BinaryTikiAnimation* binAni);
			string readString(UInt32 id);
			ITexture* readTexture(UInt32 id);

			void addPartsModel();
			void addPartsMesh(TikiMesh* mesh);
			UInt32 addPartsTexture(ITexture* tex);
			UInt32 addPartsBone(TikiBone* bone, UInt32 parentId);
			UInt32 addPartsLayer(UInt32 animationId, TikiLayer* layer);
			void addPartsAnimation(TikiAnimation* animation);
			UInt32 addPartsString(string str);

		};
	}
}