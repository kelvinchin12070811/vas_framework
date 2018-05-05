#pragma once
#include <vector>
#include "AbstractMapLayer.hpp"

namespace vas
{
	class TileLayer : public AbstractMapLayer
	{
	public:
		TileLayer();
		TileLayer(const std::vector<uint32_t>& data, uint32_t width, uint32_t height, uint8_t opacity, bool hidden);
		TileLayer(std::vector<uint32_t>&& data, uint32_t width, uint32_t height, uint8_t opacity, bool hidden);
		~TileLayer();

		uint32_t tileAt(size_t index) const;
		uint32_t tileAt(int x, int y) const;

	public: // Getters
		const std::vector<uint32_t>& getTilesData() const;
		uint32_t getWidth() const;
		uint32_t getHeight() const;
		uint8_t getOpacity() const;
		bool isHidden() const;

	public: // Setters
		void setTilesData(const std::vector<uint32_t>& value);
		void setTilesData(std::vector<uint32_t>&& value);
		void setWidth(uint32_t value);
		void setHeight(uint32_t value);

	private:
		std::vector<uint32_t> tilesData;
		uint32_t width{ 0 };
		uint32_t height{ 0 };
		uint8_t opacity;
		bool hidden{ false };
	};
}