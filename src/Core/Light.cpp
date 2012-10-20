
#include "Core/Light.h"

namespace TikiEngine
{
	namespace Components
	{
		#pragma region Class
		Light::Light(Engine* engine, GameObject* gameObject)
			: Component(engine, gameObject), color(), range(0), type(LT_None)
		{
		}

		Light::~Light()
		{
		}
		#pragma endregion

		#pragma region Member
		void Light::Draw(const DrawArgs& args)
		{
		}

		void Light::Update(const UpdateArgs& args)
		{
		}

		bool Light::GetReady()
		{
			return (type != LT_None) && (range != 0);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		Color Light::GetColor() const
		{
			return color;
		}

		void Light::SetColor(const Color& color)
		{
			this->color = color;
		}

		float Light::GetRange() const
		{
			return range;
		}

		void Light::SetRange(float range)
		{
			this->range = range;
		}

		LightType Light::GetType() const
		{
			return type;
		}

		void Light::SetType(LightType type)
		{
			this->type = type;
		}
		#pragma endregion
	}
}