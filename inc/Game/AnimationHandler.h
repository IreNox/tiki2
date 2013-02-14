#pragma once

#include "Core/IAnimation.h"
#include "Core/EventAnimation.h"

namespace TikiEngine
{
	class AnimationHandlerMGUnit : public AnimationEvent
	{
	public:

		AnimationHandlerMGUnit(IModel* model);
		~AnimationHandlerMGUnit();


		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* attack;
		IAnimation* run;
		IAnimation* death;
		IAnimation* idle;
	};

	class AnimationHandlerPlasmaUnit : public AnimationEvent
	{
	public:

		AnimationHandlerPlasmaUnit(IModel* model);
		~AnimationHandlerPlasmaUnit();


		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* attack;
		IAnimation* run;
		IAnimation* death;
		IAnimation* idle;
	};

	class AnimationHandlerHero : public AnimationEvent
	{
	public:

		AnimationHandlerHero(IModel* model);
		~AnimationHandlerHero();

		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* attack;
		IAnimation* run;

		IAnimation* idle1;
		IAnimation* idle2;
		IAnimation* idle3;


		IAnimation* death1;
		IAnimation* death2;

		IAnimation* rocket;

	};

	class AnimationHandlerSpidermine : public AnimationEvent
	{
	public:

		AnimationHandlerSpidermine(IModel* model);
		~AnimationHandlerSpidermine();

		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* idle;
		IAnimation* run;
	};

	class AnimationHandlerPlayerBase : public AnimationEvent
	{
	public:

		AnimationHandlerPlayerBase(IModel* model);
		~AnimationHandlerPlayerBase();

		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* idle;
		IAnimation* folding;
		IAnimation* folded;
		IAnimation* unfolding;
	};

	class AnimationHandlerResearchBuilding : public AnimationEvent
	{
	public:

		AnimationHandlerResearchBuilding(IModel* model);
		~AnimationHandlerResearchBuilding();

		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* idle;
		IAnimation* closing;
		IAnimation* opening;
		IAnimation* research;
	};

	class AnimationHandlerSpawn : public AnimationEvent
	{
	public:

		AnimationHandlerSpawn(IModel* model);
		~AnimationHandlerSpawn();

		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* idleopen;
		IAnimation* idleclosed;
		IAnimation* closing;
		IAnimation* opening;
		
	};
}