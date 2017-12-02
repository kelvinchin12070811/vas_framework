#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../graphics/irender_able/iRenderAble.hpp"

#define VAS_ITEM_VAR(varaible) std::wstring(L#varaible), varaible

namespace vas
{
	class Layer : public iRenderAble
	{
	public:
		struct RenderAbleHolder
		{
			std::wstring name;
			bool activated;
			std::shared_ptr<iRenderAble> instance;
		};

		Layer();
		~Layer();

		void insert(const std::wstring& name, const std::shared_ptr<iRenderAble>& instance, bool activated = true);
		void insert(const std::wstring& name, std::shared_ptr<iRenderAble>&& instance, bool activated = true);

		void remove(size_t index);
		void remove(const std::wstring& name);

		std::shared_ptr<iRenderAble> get(size_t index);
		std::shared_ptr<iRenderAble> get(const std::wstring& name);

		size_t count();
		bool isEmpty();

		void tick() override;
		void draw() override;

		void setActivated(size_t index, bool value);
		void setActivated(const std::wstring& name, bool value);

		void moveUp(size_t index, size_t distance);
		void moveUp(const std::wstring& name, size_t distance);

		void moveDown(size_t index, size_t distance);
		void moveDown(const std::wstring& name, size_t distance);

		bool getActivated(size_t index);
		bool getActivated(const std::wstring& name);

		template<typename T>
		std::shared_ptr<T> getInstance(size_t index);
		template<typename T>
		std::shared_ptr<T> getInstance(const std::wstring& name);
	private:
		std::vector<Layer::RenderAbleHolder> renderAbleList;
	};

	template<typename T>
	inline std::shared_ptr<T> Layer::getInstance(size_t index)
	{
		auto instance = get(index);
		return instance == nullptr ? nullptr : std::dynamic_pointer_cast<T>(instance);
	}

	template<typename T>
	inline std::shared_ptr<T> Layer::getInstance(const std::wstring & name)
	{
		auto instance = get(name);
		return instance == nullptr ? nullptr : std::dynamic_pointer_cast<T>(instance);
	}
}