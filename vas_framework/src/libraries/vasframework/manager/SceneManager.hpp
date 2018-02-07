#pragma once
#include <memory>
#include <vector>
#include "../VASConfig.hpp"
#include "../graphics/scene/SceneBase.hpp"

namespace vas
{
	class VAS_DECLSPEC SceneManager
	{
	public:
		static SceneManager& getInstance();

		bool isEmpty();
		bool atleast2Scene();
		void clear(bool keepLast = false);
		void call(const std::shared_ptr<SceneBase>& instance);
		void call(std::shared_ptr<SceneBase>&& instance);
		void back();
		std::shared_ptr<SceneBase> current();
		std::shared_ptr<SceneBase> previous();
		std::shared_ptr<SceneBase> getWithIndex(size_t index);
		std::shared_ptr<SceneBase> findWithThisPtr(SceneBase* instance);
		size_t instanceCount();
	private:
		SceneManager();
		~SceneManager();

		std::vector<std::shared_ptr<SceneBase>> callStack;
	};
}