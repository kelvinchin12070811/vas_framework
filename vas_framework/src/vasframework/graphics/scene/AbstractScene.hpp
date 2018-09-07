#pragma once
#include "../layer/Layers.hpp"
#include "../../VASConfig.hpp"

//Main instance of RenderAssistance
#define RenderAssistance this->__renderAssistance
//Call RenderAssistance to work
#define CallRenderAssistance \
	if (this->__renderAssistance == nullptr) \
		this->__renderAssistance = std::make_unique<vas::Layers>()
//Send back RenderAssistance
#define SendBackRenderAssistance this->__renderAssistance = nullptr

//Check if RenderAssistance is allowed to render
#define IsRenderAssistanceEnabled this->__isRenderAssistanceEnabled()
//Check if RenderAssistance is called
#define IsRenderAssistanceCalled this->__renderAssistance != nullptr
//Check if RenderAssistance is ready to work
#define IsRenderAssistanceReady IsRenderAssistanceCalled && IsRenderAssistanceEnabled

//Allow RenderAssistance to render it's contents to scene
#define EnableRenderAssistance this->__enableRenderAssistance = true
//Not allow RenderAssistance to render it's contents to scene
#define DisableRenderAssistance this->__enableRenderAssistance = false

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
		virtual void beforeTerminate();
		// Call to previous scene when current scene is terminated
		virtual void afterTerminate();
		// Call to current scene when current scene is begin to change
		virtual void beforeSceneCall();
		// Call to current scene when previous scene changed
		virtual void afterSceneCall();
	protected:
		bool __isRenderAssistanceEnabled();
	protected:
		std::unique_ptr<Layers> __renderAssistance{ nullptr };
		bool __enableRenderAssistance{ true };
	};
}