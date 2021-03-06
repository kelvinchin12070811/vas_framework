//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <memory>
#include <vector>
#include "../VASConfig.hpp"
#include "../graphics/scene/Scene.hpp"

namespace vas
{
	/**
	 * @ingroup managers
	 * @{
	 */
	/**
	 * @brief The game scene magager
	 * 
	 * The manager which controll all of the Scene of the game. All of the called scene are store in a "scene call stack",
	 * the scene on the top will always have highest priority to be called by the game loop. The second scene from the
	 * top called "previous scene" which will be called to render if Base::doubleSceneRendering is true.
	 */
	class VAS_DECLSPEC SceneManager
	{/** @} */
	public:
		/** Get the unique instance of SceneManager. */
		static SceneManager& getInstance();

		/**
		 * Check if scene call stack is empty.
		 * @return true if call stack is empty, false otherwise.
		 */
		bool isEmpty();
		/**
		 * Check if the scene call stack have at least 2 scene.
		 * @return true if 2 or more scenes in call stace.
		 */
		bool atleast2Scene();
		/**
		 * Clear the scene call stack.
		 * @param[in] keepLast Keep current scene if true.
		 */
		void clear(bool keepLast = false);
		/**
		 * Call a new scene and push it into scene call stack.
		 * @param[in] instance Scene instance to call.
		 */
		void call(std::shared_ptr<Scene> instance);
		/**
		 * Create a new instance and pushing it into the call stack, Parameters passed will be forwarded to the
		 * consstructor of targeted scene.
		 * 
		 * @tparam GenericScene Targeted Scene data type.
		 * @tparam Args Variadic arguments (or parameters) types of arguments.
		 * @param[in] args Arguments that forwarded to the constructor of the targeted Scene.
		 */
		template <class GenericScene, class... Args>
		void emplaceCall(Args&&... args)
		{
			auto ptr = new GenericScene(std::forward(args)...);
			this->call(std::shared_ptr<vas::Scene>(static_cast<vas::Scene*>(ptr)));
		}
		/**
		 * Call a new scene with its name. The target Scene's child must registered with Simple Reflection Library before called.
		 * @param sceneName Name of the scene.
		 */
		void call(const std::string& sceneName);
		/** Return to previous scene. */
		void back();
		/** Get current scene. */
		std::shared_ptr<Scene> current();
		/** Get previous scene. */
		std::shared_ptr<Scene> previous();
		/**
		 * Get scene instance with index.
		 * @param[in] index Index of the scene. The latest scene will always have the largest index as it stay at the bottom of
		 * the array.
		 */
		std::shared_ptr<Scene> getWithIndex(size_t index);
		/**
		 * Find the corresponding instance with raw pointer, usualy work with "this" pointer.
		 * @param[in] instance Raw pointer of scene instance to search.
		 * @return The corresponding instance of the raw pointer.
		 */
		std::shared_ptr<Scene> findWithThisPtr(Scene* instance);
		/**
		 * Number of scene called in call stack.
		 * @return Call count of scene call stack.
		 */
		size_t instanceCount();
		/** Capacity that allocated for call stack. */
		size_t capacity();

		void forceGC(); /**< Force SceneManager to release unused memory. */
		void shrinkToFit(); /**< Shrink callstack size to fit current objects count. */
	private:
		SceneManager();
		~SceneManager();

		std::vector<std::shared_ptr<Scene>> callStack;
	private:
		static const size_t MinStackCount{ 10 }; /**< Minimum stack count. Keep at least this amount of buffer in stack. */
		static const bool autoGC{ false }; /**< Turn auto grabage collection on or off. */
	};
}