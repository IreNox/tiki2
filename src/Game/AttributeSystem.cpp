
#include "Game/AttributeSystem.h"

#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		AttributeSystem::AttributeSystem(TikiBot* owner)
			: EngineObject(owner->GetEngine())
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
		}

		AttributeSystem::~AttributeSystem()
		{
		}

		void AttributeSystem::AddModifiert(TikiAttModifier* mod)
		{
			attributes[mod->GetAttributeType()].addModifier(mod);
		}

		void AttributeSystem::RemoveModifier(TikiAttModifier* mod)
		{
			attributes[mod->GetAttributeType()].removeModifier(mod);
		}

		TikiAtt& AttributeSystem::operator[](Attributes att)
		{
			return attributes.GetRef(att);
		}
	}
}