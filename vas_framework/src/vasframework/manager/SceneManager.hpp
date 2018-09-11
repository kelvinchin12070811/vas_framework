#pragma once
#include <memory>
#include <vector>
#include "../VASConfig.hpp"
#include "../graphics/scene/Scene.hpp"

namespace vas
{
	class VAS_DECLSPEC SceneManager
	{
	public:
		static SceneManager& getInstance();

		bool isEmpty();
		bool atleast2Scene();
		void clear(bool keepLast = false);
		void call(const std::shared_ptr<Scene>& instance);
		void call(std::shared_ptr<Scene>&& instance);
		void back();
		std::shared_ptr<Scene> current();
		std::shared_ptr<Scene> previous();
		std::shared_ptr<Scene> getWithIndex(size_t index);
		std::shared_ptr<Scene> findWithThisPtr(Scene* instance);
		size_t instanceCount();
	private:
		SceneManager();
		~SceneManager();

		std::vector<std::shared_ptr<Scene>> callStack;
	};
}