//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include <algorithm>
#include "SceneManager.hpp"
#include "../graphics/scene/SceneCallFailed.hpp"
#include "../sreflex/ReflectAbleFactory.hpp"

namespace vas
{
	const size_t SceneManager::MinStackCount;

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

		if (!keepLast)
		{
			callStack.back()->beforeTerminate();
			callStack.clear();
		}
		else
		{
			auto lastInstance = callStack.back();
			callStack.clear();
			callStack.push_back(std::move(lastInstance));

			if (!callStack.empty())
				callStack.back()->afterTerminate();
		}

		if (callStack.capacity() > SceneManager::MinStackCount * 3)
		{
			for (int loop{ 0 }; loop < 10; loop++)
				callStack.push_back(nullptr);
			callStack.shrink_to_fit();
			for (int loop{ 0 }; loop < 10; loop++)
				callStack.pop_back();
		}
	}

	void SceneManager::call(std::shared_ptr<Scene> instance)
	{
		if (instance == nullptr) throw vas::SceneCallFailed{};
		if (!callStack.empty()) callStack.back()->beforeSceneCall();
		callStack.push_back(std::move(instance));
		callStack.back()->afterSceneCall();
	}

	void SceneManager::call(const std::string & sceneName)
	{
		sreflex::ReflectAbleFactory factory;
		auto instance = factory.createObject(sceneName);
		if (instance == nullptr)
			throw SceneCallFailed{ sceneName };
		else
			call(std::shared_ptr<Scene>(dynamic_cast<Scene*>(instance.release())));
	}

	void SceneManager::back()
	{
		if (callStack.empty()) return;
		callStack.back()->beforeTerminate();
		callStack.pop_back();
		if (!callStack.empty()) callStack.back()->afterTerminate();

		if (auto capacity = callStack.capacity(); capacity > SceneManager::MinStackCount && capacity > callStack.size() * 3)
			forceGC();
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
		return *(callStack.rbegin()++);
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

	size_t SceneManager::capacity()
	{
		return callStack.capacity();
	}

	void SceneManager::forceGC()
	{
		if (callStack.capacity() > SceneManager::MinStackCount)
		{
			if (size_t size{ callStack.size() }; size >= SceneManager::MinStackCount)
			{
				callStack.shrink_to_fit();
			}
			else
			{
				size_t padding = SceneManager::MinStackCount - size;
				for (size_t i{ 0 }; i < padding; i++)
					callStack.push_back(nullptr);
				callStack.shrink_to_fit();
				for (size_t i{ 0 }; i < padding; i++)
					callStack.pop_back();
			}
		}
	}

	SceneManager::SceneManager()
	{
		callStack.reserve(10);
	}

	SceneManager::~SceneManager()
	{
	}
}