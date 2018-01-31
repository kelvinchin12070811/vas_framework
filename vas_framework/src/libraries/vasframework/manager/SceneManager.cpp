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
		return callStack.empty();
	}

	bool SceneManager::atleast2Scene()
	{
		return callStack.size() >= 2;
	}

	void SceneManager::clear(bool keepLast)
	{
		if (!keepLast)
		{
			callStack.clear();
			return;
		}
		auto lastInstance = callStack.back();
		callStack.clear();
		callStack.push_back(std::move(lastInstance));
	}

	void SceneManager::call(const std::shared_ptr<SceneBase>& instance)
	{
		if (!callStack.empty()) callStack.back()->Signal_beforeSceneCall();
		callStack.push_back(instance);
		callStack.back()->Signal_afterSceneCall();
	}

	void SceneManager::call(std::shared_ptr<SceneBase>&& instance)
	{
		if (!callStack.empty()) callStack.back()->Signal_beforeSceneCall();
		callStack.push_back(std::move(instance));
		callStack.back()->Signal_afterSceneCall();
	}

	void SceneManager::back()
	{
		if (callStack.empty()) return;
		callStack.back()->Signal_beforeTerminate();
		callStack.pop_back();
		if (!callStack.empty()) callStack.back()->Signal_afterTerminate();
	}

	std::shared_ptr<SceneBase> SceneManager::current()
	{
		if (isEmpty())
			return nullptr;
		return callStack.back();
	}

	std::shared_ptr<SceneBase> SceneManager::previous()
	{
		if (isEmpty() || callStack.size() < 2)
			return nullptr;
		return callStack[callStack.size() - 2];
	}

	std::shared_ptr<SceneBase> SceneManager::getWithIndex(size_t index)
	{
		if (callStack.empty() || index >= callStack.size())
		return callStack[index];
	}

	size_t SceneManager::instanceCount()
	{
		return callStack.size();
	}

	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
	}
}