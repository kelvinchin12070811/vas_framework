#include <algorithm>
#include <boost/format.hpp>
#include <boost/algorithm/clamp.hpp>
#include <boost/any.hpp>
#include "Layers.hpp"

namespace vas
{
	Layers::Layers()
	{
	}

	Layers::Layers(const Layers & rhs):
		layerData(rhs.layerData)
	{
	}

	Layers::Layers(Layers && rhs):
		layerData(std::move(rhs.layerData))
	{
	}

	Layers::~Layers()
	{
	}

	void Layers::insert(const LayerData & data, size_t pos)
	{
		if (pos != SIZE_MAX && pos < layerData.size())
		{
			layerData.insert(layerData.begin() + pos, data);
		}
		else
		{
			layerData.push_back(data);
		}
	}

	void Layers::insert(LayerData && data, size_t pos)
	{
		if (pos != SIZE_MAX && pos < layerData.size())
		{
			layerData.insert(layerData.begin() + pos, std::move(data));
		}
		else
		{
			layerData.push_back(std::move(data));
		}
	}

	void Layers::remove()
	{
		layerData.pop_back();
	}

	void Layers::remove(const std::string & name)
	{
		auto result = std::find_if(layerData.begin(), layerData.end(), [&](LayerData& itr)->bool
		{
			return itr.first == name;
		});
		if (result == layerData.end()) return;
		remove(std::distance(layerData.begin(), result));
	}

	void Layers::remove(size_t index)
	{
		if (index >= layerData.size()) return;
		layerData.erase(layerData.begin() + index);
	}

	size_t Layers::shift(size_t index, Layers::ShiftDirection direction, size_t count)
	{
		if (index >= layerData.size()) throw std::logic_error((boost::format("Cannot shift item at %i because this layer only contain %i item(s)") % index % layerData.size()).str());

		size_t newPos = index;
		switch (direction)
		{
		case vas::Layers::ShiftDirection::up:
			if (index == 0) return index; // Don't shift if the item is already on the very top

			//newPos = boost::algorithm::clamp(newPos - count, 0, layerData.size());
			for (size_t i = 0; i < count; i++)
			{
				if (newPos == layerData.size() - 1) break;
				newPos++;
			}
			std::rotate(this->begin() + newPos, this->begin() + index, this->begin() + index + 1);
			break;
		case vas::Layers::ShiftDirection::down:
			if (index == layerData.size() - 1) return index; // Don't shift if the item is already on the very bottom
			auto oriIndex = index;
			//newPos = boost::algorithm::clamp(newPos + count, 0, layerData.size());
			newPos = layerData.size() - 1 - newPos;
			index = layerData.size() - 1 - index;
			for (size_t i = 0; i < count; i++)
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

	void Layers::clear()
	{
		layerData.clear();
	}

	size_t Layers::size()
	{
		return layerData.size();
	}

	bool Layers::isEmpty()
	{
		return layerData.empty();
	}

	std::vector<Layers::LayerData>::iterator Layers::begin()
	{
		return layerData.begin();
	}

	std::vector<Layers::LayerData>::iterator Layers::end()
	{
		return layerData.end();
	}

	std::vector<Layers::LayerData>::reverse_iterator Layers::rbegin()
	{
		return layerData.rbegin();
	}

	std::vector<Layers::LayerData>::reverse_iterator Layers::rend()
	{
		return layerData.rend();
	}

	Layers::LayerData & Layers::get(size_t index)
	{
		if (index >= layerData.size())
		{
			throw std::logic_error((
				boost::format("The index require which is %i is greather or equal to the total count of data which is %i")
				% index % layerData.size()).str());
		}
		return layerData[index];
	}

	Layers::LayerData & Layers::get(const std::string & name)
	{
		auto result = std::find_if(layerData.begin(), layerData.end(), [&](LayerData& itr)->bool
		{
			return itr.first == name;
		});

		if (result == layerData.end())
			throw std::logic_error((boost::format("No instance of \"%s\" found") % name).str());
		else return *result;
	}

	Layers::LayerData& Layers::findWithInstance(IRendererAble * instance)
	{
		auto result = std::find_if(layerData.begin(), layerData.end(), [&](LayerData& itr)->bool
		{
			return itr.second.get() == instance;
		});

		if (result == layerData.end())
			throw std::logic_error("Could not find instance");
		else return *result;
	}

	void Layers::tick()
	{
		for (auto& itr : layerData)
		{
			if (itr.second != nullptr) itr.second->tick();
		}
	}

	void Layers::draw()
	{
		for (auto& itr : layerData)
		{
			if (itr.second != nullptr) itr.second->draw();
		}
	}

	Layers & Layers::operator=(const Layers & rhs)
	{
		layerData = rhs.layerData;
		return *this;
	}

	Layers & Layers::operator=(Layers && rhs)
	{
		layerData = std::move(rhs.layerData);
		return *this;
	}

	std::vector<Layers::LayerData>& Layers::getLayerData()
	{
		return layerData;
	}
}