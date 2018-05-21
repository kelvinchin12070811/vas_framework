#include "TileLayer.hpp"

namespace vas
{
	TileLayer::TileLayer()
	{
	}

	TileLayer::TileLayer(const std::vector<uint32_t>& data, uint32_t width, uint32_t height, uint8_t opacity, bool hidden):
		tilesData(data), width(width), height(height), opacity(opacity), hidden(hidden)
	{
	}

	TileLayer::TileLayer(std::vector<uint32_t>&& data, uint32_t width, uint32_t height, uint8_t opacity, bool hidden):
		tilesData(std::move(data)), width(width), height(height), opacity(opacity), hidden(hidden)
	{
	}

	TileLayer::~TileLayer()
	{
	}

	uint32_t TileLayer::tileAt(size_t index) const
	{
		return (index >= tilesData.size()) ? 0 : tilesData[index];
	}

	uint32_t TileLayer::tileAt(int x, int y) const
	{
		return tileAt(x + (y * width));
	}

	const std::vector<uint32_t>& TileLayer::getTilesData() const
	{
		return tilesData;
	}

	uint32_t TileLayer::getWidth() const
	{
		return width;
	}

	uint32_t TileLayer::getHeight() const
	{
		return height;
	}

	uint8_t TileLayer::getOpacity() const
	{
		return opacity;
	}

	bool TileLayer::isHidden() const
	{
		return hidden;
	}

	void TileLayer::setTilesData(const std::vector<uint32_t>& value)
	{
		if (tilesData == value) return;
		tilesData = value;
	}

	void TileLayer::setTilesData(std::vector<uint32_t>&& value)
	{
		if (tilesData == value) return;
		tilesData = std::move(value);
	}

	void TileLayer::setWidth(uint32_t value)
	{
		width = value;
	}

	void TileLayer::setHeight(uint32_t value)
	{
		height = value;
	}
}