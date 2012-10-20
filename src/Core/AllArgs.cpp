
#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawLightArgs.h"
#include "Core/InitializationArgs.h"

namespace TikiEngine
{
	const UpdateArgs UpdateArgs::Empty = UpdateArgs();
	const DrawLightArgs DrawLightArgs::Empty = DrawLightArgs();

	const DrawArgs DrawArgs::Empty = DrawArgs();
	UpdateArgs DrawArgs::UpdateEmpty = UpdateArgs::Empty;
	DrawLightArgs DrawArgs::DrawLightEmpty = DrawLightArgs::Empty;
}