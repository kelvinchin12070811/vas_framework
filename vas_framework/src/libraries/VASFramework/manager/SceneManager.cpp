#include "SceneManager.hpp"

namespace vas
{
	SceneManager & SceneManager::getInstance()
	{
		static SceneManager instance;
		return instance;
	}

	bool SceneManager::isEmpty()
	{
		return sceneCallStack.empty();
	}

	bool SceneManager::isDoubleSceneDrawingReady()
	{
		return sceneCallStack.size() > 1;
	}

	void SceneManager::call(const std::shared_ptr<SceneBase>& instance)
	{
		if (!sceneCallStack.empty()) sceneCallStack.back()->Signal_beforeSceneCall();
		sceneCallStack.push_back(instance);
		sceneCallStack.back()->Signal_afterSceneCall();
	}

	void SceneManager::back()
	{
		if (sceneCallStack.empty() || sceneCallStack.size() <= 1) return;
		sceneCallStack.back()->Signal_beforeTerminate();
		sceneCallStack.pop_back();
		sceneCallStack.back()->Signal_afterTerminate();
	}

	void SceneManager::clearAll()
	{
		sceneCallStack.clear();
	}

	std::shared_ptr<SceneBase> SceneManager::get()
	{
		return sceneCallStack.back();
	}

	std::shared_ptr<SceneBase> SceneManager::getPrev()
	{
		return sceneCallStack.size() > 1 ? sceneCallStack[sceneCallStack.size() - 2] : nullptr;
	}

	size_t SceneManager::callCount()
	{
		return sceneCallStack.size();
	}

	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
	}
}