#pragma once

namespace TikiEngine
{
	struct SoundDescription 
	{
		float MusicVolume;
		float VoiceVolume;
		float EffectVolume;

		SoundDescription()
			: MusicVolume(0.7f), VoiceVolume(1.0f), EffectVolume(0.9f)
		{
		}
	};
}