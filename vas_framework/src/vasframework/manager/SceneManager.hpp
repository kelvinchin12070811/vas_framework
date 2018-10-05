#pragma once
#include <memory>
#include <vector>
#include "../VASConfig.hpp"
#include "../graphics/scene/Scene.hpp"

namespace vas
{
	/** @addtogroup managers
		  @{
	*/
	/** @brief The game scene magager
		  
		  | Header | Namespace |
		  | : --- : | : --- : |
		  | vasframework/manager/SceneManager.hpp | vas |

		  The manager which controll all of the Scene of the game. All of the called scene are store in a "scene call stack",
		  the scene on the top will always have highest priority to be called by the game loop. The second scene from the
		  top called "previous scene" which will be called to render if Base::doubleSceneRendering is true.
	*/
	class VAS_DECLSPEC SceneManager
	{/** @} */
	public:
		/** Get the unique instance of SceneManager. */
		static SceneManager& getInstance();

		/** Check if scene call stack is empty.
			  @return true if call stack is empty, false otherwise.
		*/
		bool isEmpty();
		/** Check if the scene call stack have at least 2 scene.
			  @return true if 2 or more scenes in call stace.
		*/
		bool atleast2Scene();
		/** Clear the scene call stack.
			  @param keepLast Keep current scene if true.
		*/
		void clear(bool keepLast = false);
		/** Call a new scene and push it into scene call stack.
			  @param instance Scene instance to call.
		*/
		void call(const std::shared_ptr<Scene>& instance);
		/** Call a new scene and push it into scene call stack.
			  @param instance Scene instance to call, instance will moved.
		*/
		void call(std::shared_ptr<Scene>&& instance);
		/** Return to previous scene. */
		void back();
		/** Get current scene. */
		std::shared_ptr<Scene> current();
		/** Get previous scene. */
		std::shared_ptr<Scene> previous();
		/** Get scene instance with index.
			  @param index Index of the scene. The latest scene will always have the largest index as it stay at the bottom of
			  the array.
		*/
		std::shared_ptr<Scene> getWithIndex(size_t index);
		/** Find the corresponding instance with raw pointer, usualy work with "this" pointer.
			  @param instance Raw pointer of scene instance to search.
			  @return The corresponding instance of the raw pointer.
		*/
		std::shared_ptr<Scene> findWithThisPtr(Scene* instance);
		/** Number of scene called in call stack.
			  @return Call count of scene call stack.
		*/
		size_t instanceCount();
	private:
		SceneManager();
		~SceneManager();

		std::vector<std::shared_ptr<Scene>> callStack;
	};
}