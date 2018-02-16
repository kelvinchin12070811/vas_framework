#pragma once
#include <memory>
#include <vector>
#include "../VASConfig.hpp"
#include "../graphics/scene/AbstractScene.hpp"

namespace vas
{
	class VAS_DECLSPEC SceneManager
	{
	public:
		static SceneManager& getInstance();

		bool isEmpty();
		bool atleast2Scene();
		void clear(bool keepLast = false);
		void call(const std::shared_ptr<AbstractScene>& instance);
		void call(std::shared_ptr<AbstractScene>&& instance);
		void back();
		std::shared_ptr<AbstractScene> current();
		std::shared_ptr<AbstractScene> previous();
		std::shared_ptr<AbstractScene> getWithIndex(size_t index);
		std::shared_ptr<AbstractScene> findWithThisPtr(AbstractScene* instance);
		size_t instanceCount();
	private:
		SceneManager();
		~SceneManager();

		std::vector<std::shared_ptr<AbstractScene>> callStack;
	};
}