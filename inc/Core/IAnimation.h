#pragma  once

#include "Core/IResource.h"

namespace TikiEngine
{
	namespace Resources
	{
		enum BLENDMODE
		{
			
		};

		class IAnimation : public IResource
		{
		public :
			IAnimation() : IResource(0){}
			virtual ~IAnimation(){}


			virtual void* GetNativeResource() 
			{
				return 0;
			}
			virtual bool GetReady()
			{
				return true;
			}

			virtual string GetName() = 0;
			virtual void SetName(string name) = 0;

			virtual float GetWeight() = 0;
			virtual void SetWeight(float weight) = 0;

			virtual double GetDuration() = 0;
			virtual void SetDuration(double time) = 0;

			virtual double GetAnimationSpeed() = 0;
			virtual void SetAnimationSpeed(double speed) = 0;

			virtual bool GetLoop() = 0;
			virtual void SetLoop(bool isLoop) = 0;

			virtual bool IsFinished() = 0;

			virtual void SetNextAnimation(IAnimation* animation) = 0;
			virtual IAnimation* GetNextAnimation() = 0;

			virtual void SetPriority(int amount) = 0;
			virtual int	 GetPriority() = 0;

			virtual void Reset() = 0;

		protected:

			void loadFromStream(wcstring fileName, Stream* stream)
			{

			}
			void saveToStream(wcstring fileName, Stream* stream)
			{

			}
		};
	}
}
