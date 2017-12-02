#include "LayerData.hpp"

namespace vas
{
	using DataType = LayerData::DataType; //alais DataType
	LayerData::LayerData()
	{
	}

	LayerData::LayerData(const LayerData & other):
		layertileid(other.layertileid), opacity(other.opacity)
	{
	}

	LayerData::LayerData(LayerData && other):
		layertileid(std::move(other.layertileid)), opacity(other.opacity)
	{
	}

	LayerData::~LayerData()
	{
	}

	void LayerData::setOpacity(uint8_t value)
	{
		opacity = value;
	}

	uint8_t LayerData::getOpacity()
	{
		return opacity;
	}

	DataType::value_type LayerData::getTile(size_t x, size_t y, size_t width) const
	{
		size_t index = x + (y * width);
		if (index >= layertileid.size()) return 0;
		else return layertileid[index];
	}

	DataType::value_type LayerData::operator[](size_t index) const
	{
		return index >= layertileid.size() ? 0 : layertileid[index];
	}

	const DataType & LayerData::get() const
	{
		return layertileid;
	}

	DataType & LayerData::get()
	{
		return layertileid;
	}

	std::vector<uint32_t>* LayerData::operator->()
	{
		return &layertileid;
	}

	const DataType * LayerData::operator->() const
	{
		return &layertileid;
	}
}