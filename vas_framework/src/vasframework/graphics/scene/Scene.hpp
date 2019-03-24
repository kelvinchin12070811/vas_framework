//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <atomic>
#include "../layer/Layers.hpp"
#include"../imgui/BasicWindowPanel.hpp"
#include "../../sreflex/ReflectAbleAutoRegistrar.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup graphics
	 * @{
	 */
	/**
	 * @brief Scene is the interface of all sceen which will be presented on the screen
	 * 
	 * The scene class drive the skeleton of the stage and present the contents to the renderer.
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

		/**
		 * @name Callback signals
		 * @{
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

		/**
		 * Open new GUI panel
		 * @tparam GUIPanelType vas::imgui::WindowPanel type.
		 * @param args Parameters to pass to the consturctor.
		 * @return Corresponding child of vas::imgui::WindowPanel.
		 */
		template<typename GUIPanelType = imgui::BasicWindowPanel, typename... Args>
		GUIPanelType* openGuiPanel(Args&&... args)
		{
			guiPanel = std::make_unique<GUIPanelType>(std::forward(args)...);
			return static_cast<GUIPanelType*>(guiPanel.get());
		}
		void closeGuiPanel(); /**< Close GUI panel. */
		imgui::WindowPanel* getGuiPanel(); /**< Get GUI panel. */
		bool isGUIPanelOpened() const; /**< Determine if GUI panel is opened. */

		void pause(); /**< Paused scene. */
		void resume(); /**< Resume scene. */
		bool isPaused(); /**< Check if scene is paused. */
	protected:
		Layer layer; /**< master layer of DrawAble objects. */
	private:
		/**
		 * Determin if this scene is paused for ticking. Scene is paused if true.
		 * 
		 * ####Mutators
		 * -# void pause()
		 * -# void resume()
		 * 
		 * ####Accessors
		 * -# bool isPaused()
		 */
		std::atomic_bool paused{ false };
		std::unique_ptr<imgui::WindowPanel> guiPanel;
	};
}