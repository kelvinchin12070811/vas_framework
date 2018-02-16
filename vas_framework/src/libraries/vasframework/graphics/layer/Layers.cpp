#include <algorithm>
#include <boost/format.hpp>
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

	std::vector<Layers::LayerData>::iterator & Layers::begin()
	{
		return layerData.begin();
	}

	std::vector<Layers::LayerData>::iterator & Layers::end()
	{
		return layerData.end();
	}

	std::vector<Layers::LayerData>::reverse_iterator & Layers::rbegin()
	{
		return layerData.rbegin();
	}

	std::vector<Layers::LayerData>::reverse_iterator & Layers::rend()
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