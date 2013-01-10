
#include "Game/AttributeSystem.h"

#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		AttributeSystem::AttributeSystem(Engine* engine)
			: EngineObject(engine)
		{
			Attributes atts[] = {
				TIKI_ALL_ATTRIBUTES
			};
			UInt32 count = sizeof(atts) / sizeof(Attributes);

			UInt32 i = 0;
			while (i < count)
			{
				attributes.Add(
					atts[i],
					TikiAtt(atts[i])
				);

				i++;
			}

			attributes.Optimize();
		}

		AttributeSystem::~AttributeSystem()
		{
		}

		void AttributeSystem::AddModifier(TikiAttModifier* mod)
		{
			attributes[mod->GetAttributeType()].addModifier(mod);
		}

		void AttributeSystem::RemoveModifier(TikiAttModifier* mod)
		{
			attributes[mod->GetAttributeType()].removeModifier(mod);
		}

		void AttributeSystem::UpdateModifier(TikiAttModifier* mod)
		{
			attributes[mod->GetAttributeType()].update();
		}
	}
}