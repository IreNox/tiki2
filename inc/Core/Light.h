#pragma once

#include "Core/Component.h"
#include "Core/Color.h"

namespace TikiEngine
{
	namespace Components
	{
		enum LightType
		{
			LT_None,
			LT_Point,
			LT_Directional,
			LT_Spot
		};

		class Light : public Component
		{
		public:

			Light(Engine* engine, GameObject* gameObject);
			~Light();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			Color GetColor() const;
			void SetColor(const Color& color);

			float GetRange() const;
			void SetType(float range);

			LightType GetType() const;
			void SetType(LightType type);

			bool GetReady();

		private:

			Color color;
			float range;

			LightType type;
		};
	}
}

