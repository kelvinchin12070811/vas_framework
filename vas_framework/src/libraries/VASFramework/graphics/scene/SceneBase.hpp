#pragma once
#include <SDL.h>
#include <memory>
#include "../../../sreflex/IObjectAutoRegister.hpp"
#include "../../containers/Layer.hpp"

#define RenderAssistance this->_renderAssistance
#define CallRenderAssistance if (RenderAssistance == nullptr) RenderAssistance = std::make_shared<vas::Layer>()

namespace vas
{
	class SceneBase : public sreflex::IObject
	{
	public:
		SceneBase();
		virtual ~SceneBase();

		virtual void tick();
		virtual void draw();

		// Call to current scene when begin terminate
		virtual void Signal_beforeTerminate();
		// Call to previous scene when current scene is terminated
		virtual void Signal_afterTerminate();
		// Call to current scene when current scene is begin to change
		virtual void Signal_beforeSceneCall();
		// Call to current scene when previous scene changed
		virtual void Signal_afterSceneCall();
	protected:
		std::shared_ptr<Layer> _renderAssistance = nullptr;
	};
}