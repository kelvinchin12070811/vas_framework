#pragma once
#include "../../sreflex/IObject.hpp"
#include "../../VASConfig.hpp"
namespace vas
{
	class VAS_DECLSPEC SceneBase : public vas::sreflex::IObject
	{
	public:
		SceneBase();
		virtual ~SceneBase();

		virtual void tick() = 0;
		virtual void draw() = 0;

		// Call to current scene when begin terminate
		virtual void Signal_beforeTerminate();
		// Call to previous scene when current scene is terminated
		virtual void Signal_afterTerminate();
		// Call to current scene when current scene is begin to change
		virtual void Signal_beforeSceneCall();
		// Call to current scene when previous scene changed
		virtual void Signal_afterSceneCall();
	};
}