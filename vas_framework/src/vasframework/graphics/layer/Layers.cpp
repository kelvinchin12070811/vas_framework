//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include <algorithm>
#include <boost/format.hpp>
#include <boost/algorithm/clamp.hpp>
#include <boost/any.hpp>
#include "Layers.hpp"

namespace vas
{
	bool Layer::autoGC{ true };
	size_t Layer::minLayerCount{ 10 };

	Layer::Layer(const Layer & rhs):
		layerData(rhs.layerData)
	{
	}

	Layer::Layer(Layer && rhs) noexcept:
		layerData(std::move(rhs.layerData))
	{
	}

	Layer::LayerData& Layer::insert(LayerData data, size_t pos)
	{
		if (pos != std::numeric_limits<size_t>::max() && pos < layerData.size())
		{
			return *(layerData.insert(layerData.begin() + pos, std::move(data)));
		}
		else
		{
			layerData.push_back(std::move(data));
			return layerData.back();
		}
	}

	void Layer::remove()
	{
		layerData.pop_back();

		if (!Layer::autoGC) return;

		if (auto cap = layerData.capacity();  cap > Layer::minLayerCount && cap > Layer::minLayerCount * 3)
			forceGC();
	}

	void Layer::remove(const DrawAble * instance)
	{
		auto result = std::find_if(layerData.begin(), layerData.end(), [&](decltype(layerData)::const_reference itr) {
			return itr.instance.get() == instance;
		});
		if (result == layerData.end()) return;
		remove(std::distance(layerData.begin(), result));
	}

	void Layer::remove(size_t index)
	{
		if (index >= layerData.size()) return;
		layerData.erase(layerData.begin() + index);
	}

	size_t Layer::shift(size_t index, Layer::ShiftDirection direction, size_t count)
	{
		if (index >= layerData.size()) throw std::logic_error{ (boost::format{ "Cannot shift item at %i because this layer only contain %i item(s)" } % index % layerData.size()).str() };

		size_t newPos{ index };
		switch (direction)
		{
		case vas::Layer::ShiftDirection::up:
			if (index == 0) return index; // Don't shift if the item is already on the very top

			//newPos = boost::algorithm::clamp(newPos - count, 0, layerData.size());
			for (size_t i{ 0 }; i < count; i++)
			{
				if (newPos == layerData.size() - 1) break;
				newPos++;
			}
			std::rotate(this->begin() + newPos, this->begin() + index, this->begin() + index + 1);
			break;
		case vas::Layer::ShiftDirection::down:
			if (index == layerData.size() - 1) return index; // Don't shift if the item is already on the very bottom
			auto oriIndex = index;
			//newPos = boost::algorithm::clamp(newPos + count, 0, layerData.size());
			newPos = layerData.size() - 1 - newPos;
			index = layerData.size() - 1 - index;
			for (size_t i{ 0 }; i < count; i++)
			{
				if (newPos == 0) break;
				newPos--;
			}
			std::rotate(this->rbegin() + newPos, this->rbegin() + index, this->rbegin() + index + 1);
			return oriIndex;
			break;
		}
		return newPos;
	}

	void Layer::clear()
	{
		layerData.clear();
		forceGC();
	}

	size_t Layer::size()
	{
		return layerData.size();
	}

	bool Layer::isEmpty()
	{
		return layerData.empty();
	}

	void Layer::forceGC()
	{
		if (layerData.capacity() <= Layer::minLayerCount * 3) return;

		if (auto size = layerData.size(); size > Layer::minLayerCount)
		{
			layerData.shrink_to_fit();
		}
		else
		{
			auto padding = Layer::minLayerCount - size;
			for (size_t i{ 0 }; i < padding; i++)
				layerData.push_back({ nullptr, false });

			layerData.shrink_to_fit();

			for (size_t i{ 0 }; i < padding; i++)
				layerData.pop_back();
		}
	}

	std::vector<Layer::LayerData>::iterator Layer::begin()
	{
		return layerData.begin();
	}

	std::vector<Layer::LayerData>::iterator Layer::end()
	{
		return layerData.end();
	}

	std::vector<Layer::LayerData>::reverse_iterator Layer::rbegin()
	{
		return layerData.rbegin();
	}

	std::vector<Layer::LayerData>::reverse_iterator Layer::rend()
	{
		return layerData.rend();
	}

	Layer::LayerData & Layer::get(size_t index)
	{
		if (index >= layerData.size())
		{
			throw std::logic_error{ (
				boost::format{"The index require which is %i is greather or equal to the total count of data which is %i"}
				% index % layerData.size()).str() };
		}
		return layerData[index];
	}

	Layer::LayerData& Layer::get(DrawAble * instance)
	{
		auto result = std::find_if(layerData.begin(), layerData.end(), [&](LayerData& itr)->bool
		{
			return itr.instance.get() == instance;
		});

		if (result == layerData.end())
			throw std::logic_error{ "Could not find instance" };
		else return *result;
	}

	std::optional<size_t> Layer::indexOf(DrawAble * instance)
	{
		auto result = std::find_if(layerData.begin(), layerData.end(), [&](decltype(layerData)::reference itr) {
			return itr.instance.get() == instance;
		});
		if (result == layerData.end()) return {};
		
		return std::distance(layerData.begin(), result);
	}

	void Layer::setAutoGC(bool value)
	{
		Layer::autoGC = value;
	}

	void Layer::setMinLayerCount(size_t value)
	{
		Layer::minLayerCount = value;
	}

	void Layer::tick()
	{
		for (auto& itr : layerData)
		{
			if (itr.instance != nullptr) itr.instance->tick();
		}
	}

	void Layer::draw(sdl::Renderer* renderer, Camera* camera)
	{
		for (auto& itr : layerData)
		{
			if (!itr.visible) return;
			if (itr.instance != nullptr) itr.instance->draw(renderer, camera);
		}
	}

	Layer & Layer::operator=(const Layer & rhs)
	{
		layerData = rhs.layerData;
		return *this;
	}

	Layer & Layer::operator=(Layer && rhs) noexcept
	{
		layerData = std::move(rhs.layerData);
		return *this;
	}

	std::vector<Layer::LayerData>& Layer::getLayerData()
	{
		return layerData;
	}

	Layer::LayerData::LayerData(std::shared_ptr<DrawAble> instance, bool visible):
		instance(std::move(instance)), visible(visible)
	{
	}
}