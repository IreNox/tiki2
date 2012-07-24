
#include "Core/Engine.h"
#include "Core/Element.h"

namespace TikiEngine
{
	Element::Element(Engine* engine)
		: engine(engine)
	{
		this->device = engine->graphics->GetDevice();
		this->context = engine->graphics->GetDeviceContext();
	}
}