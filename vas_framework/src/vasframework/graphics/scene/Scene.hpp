#pragma once
#include "../layer/Layers.hpp"
#include "../../sreflex/ReflectAbleAutoRegistrar.hpp"
#include "../../VASConfig.hpp"

#define RenderAssistance this->__renderAssistance
#define CallRenderAssistance \
	if (this->__renderAssistance == nullptr) \
		this->__renderAssistance = std::make_unique<vas::Layers>()
#define SendBackRenderAssistance this->__renderAssistance = nullptr
#define IsRenderAssistanceEnabled this->__isRenderAssistanceEnabled()
#define IsRenderAssistanceCalled this->__renderAssistance != nullptr
#define IsRenderAssistanceReady IsRenderAssistanceCalled && IsRenderAssistanceEnabled
#define EnableRenderAssistance this->__enableRenderAssistance = true
#define DisableRenderAssistance this->__enableRenderAssistance = false

namespace vas
{
	/** @addtogroup scene
		  @{
	*/
	/** @brief Scene is the interface of all sceen which will be presented on the screen

		  The scene class drive the skeleton of the stage and present the contents to the renderer.
	*/
	class VAS_DECLSPEC Scene : public sreflex::ReflectAble
	{/** @} */
	public:
		Scene() = default;
		virtual ~Scene() = default;

		/** Tick/update the scene */
		virtual void tick() = 0;
		/** Draw/render the scene */
		virtual void draw() = 0;

		/** @name Callback signals
			  @{
		*/
		/** Call to current scene when current scene is poped */
		virtual void beforeTerminate();
		/** Call to previous scene after current scene is poped */
		virtual void afterTerminate();
		/** Call to current scene when new scene is called */
		virtual void beforeSceneCall();
		/** Call to current scene when current scene is loaded */
		virtual void afterSceneCall();
		/** @} */
	protected:
		bool __isRenderAssistanceEnabled();
	protected:
		std::unique_ptr<Layers> __renderAssistance{ nullptr };
		bool __enableRenderAssistance{ true };
	};
}