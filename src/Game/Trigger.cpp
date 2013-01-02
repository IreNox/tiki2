#include "Game/Trigger.h"
#include "Core/HelperLog.h"

namespace TikiEngine
{
	namespace AI
	{
		Trigger::Trigger(GameState* gameState, GameObject* gameObject)
			: BaseGameEntity(gameState, gameObject)
		{
			boxCollider = engine->librarys->CreateComponent<IBoxCollider>(gameObject);
			boxCollider->AddRef();
			boxCollider->TriggerEnter.AddHandler(this);
			boxCollider->TriggerExit.AddHandler(this);

			// set default porps
			boxCollider->SetMaterial(gameState->GetDefaultMaterial());
			boxCollider->SetDynamic(false);
			boxCollider->SetCenter(Vector3(0, 0, 0));
			boxCollider->SetSize(Vector3(1, 1, 1));
			boxCollider->SetTrigger(true);
			boxCollider->SetGroup(CG_Collidable_Non_Pushable);

			needUpdate = true;
		}

		Trigger::~Trigger()
		{
			boxCollider->TriggerExit.RemoveHandler(this);
			boxCollider->TriggerEnter.RemoveHandler(this);
			SafeRelease(&boxCollider);
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
			// only do this once
			if (needUpdate)
			{
				needUpdate = false;
				boxCollider->SetCenter(gameObject->PRS.GPosition());
				boxCollider->SetSize(gameObject->PRS.GScale());
				boxCollider->SetGroup(CG_Collidable_Non_Pushable);
			}

		}

	}
}