#include <algorithm>
#include "SceneManager.hpp"
#include "../graphics/scene/SceneCallFailed.hpp"
#include "../sreflex/ReflectAbleFactory.hpp"

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

		callStack.back()->beforeTerminate();
		if (!keepLast)
		{
			callStack.clear();
			return;
		}
		auto lastInstance = callStack.back();
		callStack.clear();
		callStack.push_back(std::move(lastInstance));

		if (!callStack.empty())
			callStack.back()->afterTerminate();
	}

	void SceneManager::call(const std::shared_ptr<Scene>& instance)
	{
		if (instance == nullptr) throw vas::SceneCallFailed();
		if (!callStack.empty()) callStack.back()->beforeSceneCall();
		callStack.push_back(instance);
		callStack.back()->afterSceneCall();
	}

	void SceneManager::call(std::shared_ptr<Scene>&& instance)
	{
		if (instance == nullptr) throw vas::SceneCallFailed();

		if (!callStack.empty()) callStack.back()->beforeSceneCall();
		callStack.push_back(std::move(instance));
		callStack.back()->afterSceneCall();
	}

	void SceneManager::call(const std::string & sceneName)
	{
		sreflex::ReflectAbleFactory factory;
		auto instance = factory.createObject(sceneName).release();
		if (instance == nullptr)
			throw SceneCallFailed(sceneName);
		else
			call(std::shared_ptr<Scene>(dynamic_cast<Scene*>(instance)));
	}

	void SceneManager::back()
	{
		if (callStack.empty()) return;
		callStack.back()->beforeTerminate();
		callStack.pop_back();
		if (!callStack.empty()) callStack.back()->afterTerminate();
	}

	std::shared_ptr<Scene> SceneManager::current()
	{
		if (isEmpty())
			return nullptr;
		return callStack.back();
	}

	std::shared_ptr<Scene> SceneManager::previous()
	{
		if (isEmpty() || callStack.size() < 2)
			return nullptr;
		return callStack[callStack.size() - 2];
	}

	std::shared_ptr<Scene> SceneManager::getWithIndex(size_t index)
	{
		if (callStack.empty() || index >= callStack.size()) return nullptr;
		return callStack[index];
	}

	std::shared_ptr<Scene> SceneManager::findWithThisPtr(Scene * instance)
	{
		auto result = std::find_if(callStack.begin(), callStack.end(), [&](const std::shared_ptr<Scene>& value)-> bool
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