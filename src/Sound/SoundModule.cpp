#ifdef _WIN64
#pragma comment(lib, "fmodex64_vc.lib")
#else
#pragma comment(lib, "fmodex_vc.lib")
#endif

#include "Sound/SoundModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		SoundModule::SoundModule(Engine* engine)
			: ISoundSystem(engine), system(0)
		{
		}

		SoundModule::~SoundModule()
		{
		}
		#pragma endregion

		#pragma region Init
		bool SoundModule::Initialize(EngineDescription& desc)
		{
			FMOD_RESULT r = System_Create(&system);

			if (FAILED(r))
			{
				this->Dispose();
				return false;
			}

			UInt32 version = 0;
			r = system->getVersion(&version);

			if (version < FMOD_VERSION)
			{
				//printf("Error! You are using an old version of FMOD %08x. This program requires %08x\n", version, FMOD_VERSION);
				return false;
			}

			Int32 numDrivers = 0;
			r = system->getNumDrivers(&numDrivers);

			if (FAILED(r))
			{
				this->Dispose();
				return false;
			}

			if (numDrivers == 0)
			{
				r = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);

				if (FAILED(r))
				{
					this->Dispose();
					return false;
				}
			}
			else
			{
				FMOD_CAPS caps;
				FMOD_SPEAKERMODE speakerMode;
				r = system->getDriverCaps(0, &caps, 0, &speakerMode);

				if (FAILED(r))
				{
					this->Dispose();
					return false;
				}

				/*
				Set the user selected speaker mode.
				*/
				r = system->setSpeakerMode(speakerMode);
				if (FAILED(r))
				{
					this->Dispose();
					return false;
				}

				if (caps & FMOD_CAPS_HARDWARE_EMULATED)
				{
					/*
					The user has the 'Acceleration' slider set to off! This is really bad
					for latency! You might want to warn the user about this.
					*/
					r = system->setDSPBufferSize(1024, 10);
					if (FAILED(r))
					{
						this->Dispose();
						return false;
					}
				}

				char name[256];
				r = system->getDriverInfo(0, name, 256, 0);
				if (FAILED(r))
				{
					this->Dispose();
					return false;
				}

				if (strstr(name, "SigmaTel"))
				{
					/*
					Sigmatel sound devices crackle for some reason if the format is PCM 16bit.
					PCM floating point output seems to solve it.
					*/
					r = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
					if (FAILED(r))
					{
						this->Dispose();
						return false;
					}
				}
			}

			r = system->init(100, FMOD_INIT_NORMAL, 0);
			if (r == FMOD_ERR_OUTPUT_CREATEBUFFER)
			{
				/*
				Ok, the speaker mode selected isn't supported by this soundcard. Switch it
				back to stereo...
				*/
				r = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
				if (FAILED(r))
				{
					this->Dispose();
					return false;
				}

				/*
				... and re-init.
				*/
				r = system->init(100, FMOD_INIT_NORMAL, 0);
			}

			if (FAILED(r))
			{
				this->Dispose();
				return false;
			}

			return true;
		}
		#pragma endregion

		#pragma region Member
		FMOD::Sound* SoundModule::LoadSound(Stream* stream)
		{
			Sound* sound = 0;
			
			char* data = new char[stream->GetLength()];
			stream->Read(data, 0, stream->GetLength());

			FMOD_CREATESOUNDEXINFO info;
			ZeroMemory(&info, sizeof(info));
			info.cbsize = sizeof(info);
			info.length = stream->GetLength();

			system->createStream(data, FMOD_OPENMEMORY, &info, &sound);
			//system->createStream(fileName, FMOD_DEFAULT, 0, &sound);

			return sound;
		}
		#pragma endregion

		#pragma region Member - Begin/End
		void SoundModule::Begin()
		{
		}

		void SoundModule::End()
		{
		}
		#pragma endregion

		#pragma region Member - Dispose
		void SoundModule::Dispose()
		{
			if (system != 0)
			{
				system->release();
				system = 0;
			}
		}
		#pragma endregion
				
		void SoundModule::Play(ISound* sound)
		{
			FMOD::Sound* natSound = (FMOD::Sound*)sound->GetNativeResource();
			FMOD::Channel* ch = 0;
			
			system->playSound(FMOD_CHANNEL_FREE, natSound, false, &ch);
			//ch->
			//ch->setVolume()
		}
	}
}