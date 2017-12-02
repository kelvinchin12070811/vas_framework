#include "Layer.hpp"
#include <algorithm>

namespace vas
{
	Layer::Layer()
	{
	}


	Layer::~Layer()
	{
	}

	void Layer::insert(const std::wstring & name, const std::shared_ptr<iRenderAble>& instance, bool activated)
	{
		renderAbleList.push_back({ name, activated, instance });
	}

	void Layer::insert(const std::wstring & name, std::shared_ptr<iRenderAble>&& instance, bool activated)
	{
		renderAbleList.push_back({ name, activated, std::move(instance) });
	}

	void Layer::remove(size_t index)
	{
		if (index >= renderAbleList.size()) return;
		renderAbleList.erase(renderAbleList.begin() + index);
	}

	void Layer::remove(const std::wstring & name)
	{
		auto result = std::find_if(renderAbleList.begin(), renderAbleList.end(), [&](const RenderAbleHolder& instance)->bool{
			return instance.name == name;
		});

		if (result == renderAbleList.end()) return;
		renderAbleList.erase(result);
	}

	std::shared_ptr<iRenderAble> Layer::get(size_t index)
	{
		return index < renderAbleList.size() ? renderAbleList[index].instance : nullptr;
	}

	std::shared_ptr<iRenderAble> Layer::get(const std::wstring & name)
	{
		auto result = std::find_if(renderAbleList.begin(), renderAbleList.end(), [&](RenderAbleHolder& instance)->bool {return instance.name == name; });
		return result == renderAbleList.end() ? nullptr : result->instance;
	}

	size_t Layer::count()
	{
		return renderAbleList.size();
	}

	bool Layer::isEmpty()
	{
		return renderAbleList.empty();
	}

	void Layer::tick()
	{
		for (const auto& listItr : renderAbleList)
			if (listItr.instance)
				if (listItr.activated) listItr.instance->tick();
	}

	void Layer::draw()
	{
		for (const auto& listItr : renderAbleList)
			if (listItr.instance)
				if (listItr.activated) listItr.instance->draw();
	}

	void Layer::setActivated(size_t index, bool value)
	{
		if (index >= renderAbleList.size()) return;
		renderAbleList[index].activated = value;
	}

	void Layer::setActivated(const std::wstring & name, bool value)
	{
		auto result = std::find_if(renderAbleList.begin(), renderAbleList.end(), [&](const RenderAbleHolder& instance)->bool{
			return instance.name == name;
		});
		if (result != renderAbleList.end())
			result->activated = value;
	}

	void Layer::moveUp(size_t index, size_t distance)
	{
		if (index >= renderAbleList.size()) return;
		if (index == 0) return; //return if try to move first element
		int64_t targetedPosition = static_cast<int64_t>(index) - static_cast<int64_t>(distance);
		if (targetedPosition <= 0)
			targetedPosition = 0;

		RenderAbleHolder tempInstance = std::move(renderAbleList[index]);
		renderAbleList.erase(renderAbleList.begin() + index);
		renderAbleList.insert(renderAbleList.begin() + static_cast<size_t>(targetedPosition), std::move(tempInstance));
	}

	void Layer::moveUp(const std::wstring & name, size_t distance)
	{
		auto result = std::find_if(renderAbleList.begin(), renderAbleList.end(), [&](const RenderAbleHolder& instance)->bool {
			return instance.name == name;
		});
		moveUp(std::distance(renderAbleList.begin(), result), distance);
	}

	void Layer::moveDown(size_t index, size_t distance)
	{
		if (index >= renderAbleList.size()) return;
		if (index == renderAbleList.size() - 1) return; //return if try to move last element
		int64_t targetedPosition = static_cast<int64_t>(index) + static_cast<int64_t>(distance);
		if (targetedPosition >= static_cast<int64_t>(renderAbleList.size()))
			targetedPosition = static_cast<int64_t>(renderAbleList.size()) - 1;

		RenderAbleHolder tempInstance = std::move(renderAbleList[index]);
		renderAbleList.erase(renderAbleList.begin() + index);
		renderAbleList.insert(renderAbleList.begin() + static_cast<size_t>(targetedPosition), std::move(tempInstance));
	}

	void Layer::moveDown(const std::wstring & name, size_t distance)
	{
		auto result = std::find_if(renderAbleList.begin(), renderAbleList.end(), [&](const RenderAbleHolder& instance) {
			return instance.name == name;
		});
		moveDown(std::distance(renderAbleList.begin(), result), distance);
	}

	bool Layer::getActivated(size_t index)
	{
		return index >= renderAbleList.size() ? false : renderAbleList[index].activated;
	}

	bool Layer::getActivated(const std::wstring & name)
	{
		auto result = std::find_if(renderAbleList.begin(), renderAbleList.end(), [&](const RenderAbleHolder& instance)->bool {
			return instance.name == name;
		});
		return getActivated(std::distance(renderAbleList.begin(), result));
	}
}