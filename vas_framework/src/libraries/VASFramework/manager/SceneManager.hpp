#pragma once
#include <memory>
#include <vector>
#include "../graphics/scene/SceneBase.hpp"

namespace vas
{
	class SceneManager
	{
	public:
		static SceneManager& getInstance();

		bool isEmpty();
		bool isDoubleSceneDrawingReady();

		void call(const std::shared_ptr<SceneBase>& instance);
		void back();
		void clearAll();

		std::shared_ptr<SceneBase> get();
		std::shared_ptr<SceneBase> getPrev();
		size_t callCount();

		inline SceneBase* currentScene() { return get().get(); };
		inline SceneBase* prevScene() { return getPrev().get(); };
	private:
		SceneManager();
		~SceneManager();

		std::vector<std::shared_ptr<SceneBase>> sceneCallStack;
	};
	inline SceneManager& SceneManagerAPI() { return SceneManager::getInstance(); };
}