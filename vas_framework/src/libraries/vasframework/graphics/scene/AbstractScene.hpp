#pragma once
#include "../layer/Layers.hpp"
#include "../../VASConfig.hpp"

#define RenderAssistance this->__renderAssistance
#define CallRenderAssistance \
	if (this->__renderAssistance == nullptr) \
		this->__renderAssistance = std::make_unique<vas::Layers>()

namespace vas
{
	class VAS_DECLSPEC AbstractScene
	{
	public:
		AbstractScene();
		virtual ~AbstractScene();

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
	protected:
		std::unique_ptr<Layers> __renderAssistance{ nullptr };
	};
}