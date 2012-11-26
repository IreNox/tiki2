#include "Game/Trigger.h"
#include "Core/HelperLog.h"

namespace TikiEngine
{
	namespace AI
	{
		Trigger::Trigger(GameState* gameState, GameObject* gameObject)
			: BaseGameEntity(gameState, gameObject)
		{
			pos = Vector3::Zero;

			boxCollider = engine->librarys->CreateComponent<IBoxCollider>(gameObject);
			boxCollider->AddRef();
			boxCollider->TriggerEnter.AddHandler(this);
			boxCollider->TriggerExit.AddHandler(this);

			// set default porps
			boxCollider->SetMaterial(0);
			boxCollider->SetDynamic(false);
			boxCollider->SetCenter(pos);
			boxCollider->SetSize(Vector3(1, 1, 1));
			boxCollider->SetTrigger(true);
			boxCollider->SetGroup(CG_Collidable_Non_Pushable);


			needUpdate = false;
		}

		Trigger::~Trigger()
		{
			boxCollider->TriggerExit.RemoveHandler(this);
			boxCollider->TriggerEnter.RemoveHandler(this);
			SafeRelease(&boxCollider);
		}

		void Trigger::Init(const Vector3& size)
		{
			// set porps
			boxCollider->SetSize(size);
			needUpdate = true;
		}

		void Trigger::Handle(ICollider* sender, const TriggerEnterArgs& args)
		{
			engine->HLog.Write("Trigger Enter");
		}

		void Trigger::Handle(ICollider* sender, const TriggerExitArgs& args)
		{
			engine->HLog.Write("Trigger Exit");
		}

		void Trigger::Update(const UpdateArgs& args)
		{
			if (needUpdate)
			{
				needUpdate = false;
				boxCollider->SetCenter(gameObject->PRS.GPosition());
				boxCollider->SetGroup(CG_Collidable_Non_Pushable);
			}

		}

	}
}