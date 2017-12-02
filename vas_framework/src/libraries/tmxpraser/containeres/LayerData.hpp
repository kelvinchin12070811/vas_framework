#pragma once
#include <vector>

namespace vas
{
	class LayerData
	{
	public:
		using DataType = std::vector<uint32_t>;
		LayerData();
		LayerData(const LayerData& other);
		LayerData(LayerData&& other);

		~LayerData();

		void setOpacity(uint8_t value);
		uint8_t getOpacity();

		DataType::value_type getTile(size_t x, size_t y, size_t width) const;
		DataType::value_type operator[](size_t index) const;
		const DataType& get() const;
		DataType& get();
		DataType* operator->();
		const DataType* operator->() const;
	private:
		DataType layertileid;
		uint8_t opacity = 255;
	};
}