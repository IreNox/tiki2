#pragma once

#include "Core/Event.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IModel;
	}
	using namespace Resources;

	enum AnimationType
	{
		AT_Idle,
		AT_Attack,
		AT_Run,
		AT_Death,

		AT_Rocket,

		AT_Folding,
		AT_UnFolding,
		AT_Folded
	};
	
	struct AnimationArgs
	{
		AnimationType animationType;
		IAnimation* animation;
		AnimationArgs(AnimationType type = AT_Run) : animationType(type) , animation(0) {}
		
	};

	//class AnimationEvent: public Event<IModel, AnimationArgs>
	//{
	//public:
	//	~AnimationEvent()
	//	{
	//		for(UINT i = 0; i < eventHandler.Count(); i++)
	//			SafeDelete(&eventHandler[i]);
	//	}
	//};

	class AnimationEvent : public Event<IModel, AnimationArgs>
	{
	public:
		~AnimationEvent()
		{
			for(UINT i = 0; i < eventHandler.Count(); i++)
			{
				SafeDelete(&eventHandler[i]);
			}
		}

		void RaiseAnimationEvent(IModel* sender, AnimationArgs& args)
		{
			FindMappedAnimation(args);
			RaiseEvent(sender, args);
		}

	private :
		virtual void FindMappedAnimation(AnimationArgs& args)
		{
		}
	};

	class AnimationEventHandler : public EventHandler<IModel, AnimationArgs>
	{
	public:
		void Handle(IModel* sender, const AnimationArgs& args);
	};


	//typedef Event<IModel, AnimationArgs> AnimationEvent;
	//typedef EventHandler<IModel, AnimationArgs> AnimationEventHandler;
}