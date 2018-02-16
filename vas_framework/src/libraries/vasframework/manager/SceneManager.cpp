#include <algorithm>
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
		if (callStack.empty()) return;

		callStack.back()->Signal_beforeTerminate();
		if (!keepLast)
		{
			callStack.clear();
			return;
		}
		auto lastInstance = callStack.back();
		callStack.clear();
		callStack.push_back(std::move(lastInstance));

		if (!callStack.empty())
			callStack.back()->Signal_afterTerminate();
	}

	void SceneManager::call(const std::shared_ptr<AbstractScene>& instance)
	{
		if (!callStack.empty()) callStack.back()->Signal_beforeSceneCall();
		callStack.push_back(instance);
		callStack.back()->Signal_afterSceneCall();
	}

	void SceneManager::call(std::shared_ptr<AbstractScene>&& instance)
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

	std::shared_ptr<AbstractScene> SceneManager::current()
	{
		if (isEmpty())
			return nullptr;
		return callStack.back();
	}

	std::shared_ptr<AbstractScene> SceneManager::previous()
	{
		if (isEmpty() || callStack.size() < 2)
			return nullptr;
		return callStack[callStack.size() - 2];
	}

	std::shared_ptr<AbstractScene> SceneManager::getWithIndex(size_t index)
	{
		if (callStack.empty() || index >= callStack.size()) return nullptr;
		return callStack[index];
	}

	std::shared_ptr<AbstractScene> SceneManager::findWithThisPtr(AbstractScene * instance)
	{
		auto result = std::find_if(callStack.begin(), callStack.end(), [&](const std::shared_ptr<AbstractScene>& value)-> bool
		{
			return value.get() == instance;
		});
		if (result == callStack.end())
			return nullptr;
		return *result;
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