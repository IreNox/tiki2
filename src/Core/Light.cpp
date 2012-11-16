
#include "Core/Light.h"
#include "Core/GameObject.h"

#include "Core/IGraphics.h"

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
#if _DEBUG
			Vector3 pos = gameObject->PRS.GPosition();

			// Axis align
			engine->graphics->DrawLine(
				pos - Vector3(-0.25f, 0, 0), pos + Vector3(-0.25f, 0, 0), Color::Yellow
			);

			engine->graphics->DrawLine(
				pos - Vector3(0, -0.25f, 0), pos + Vector3(0, -0.25f, 0), Color::Yellow
			);

			engine->graphics->DrawLine(
				pos - Vector3(0, 0, -0.25f), pos + Vector3(0, 0, -0.25f), Color::Yellow
			);

			// Diagonal
			engine->graphics->DrawLine(
				pos - Vector3(-0.125f, -0.125f, 0), pos + Vector3(-0.125f, -0.125f, 0), Color::Yellow
			);

			engine->graphics->DrawLine(
				pos - Vector3(0, -0.125f, -0.125f), pos + Vector3(0, -0.125f, -0.125f), Color::Yellow
			);

			engine->graphics->DrawLine(
				pos - Vector3(-0.125f, 0, -0.125f), pos + Vector3(-0.125f, 0, -0.125f), Color::Yellow
			);

			engine->graphics->DrawLine(
				pos - Vector3(-0.125f, -0.125f, -0.125f), pos + Vector3(-0.125f, -0.125f, -0.125f), Color::Yellow
			);

			// Direction
			engine->graphics->DrawLine(
				pos, pos + gameObject->PRS.GetForward(), Color::Red
			);
#endif
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