#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../IRenderAble.hpp"

namespace vas
{
	class Layers : public IRendererAble
	{
	public:
		using LayerData = std::pair<std::string, std::shared_ptr<IRendererAble>>;
		Layers();
		Layers(const Layers& rhs);
		Layers(Layers&& rhs);
		~Layers();

		void insert(const LayerData& data, size_t pos = SIZE_MAX);
		void insert(LayerData&& data, size_t pos = SIZE_MAX);
		
		void remove();
		void remove(const std::string& name);
		void remove(size_t index);

		void clear();
		size_t size();
		bool isEmpty();

		std::vector<Layers::LayerData>::iterator& begin();
		std::vector<Layers::LayerData>::iterator& end();
		std::vector<Layers::LayerData>::reverse_iterator& rbegin();
		std::vector<Layers::LayerData>::reverse_iterator& rend();

		LayerData& get(size_t index);
		LayerData& get(const std::string& name);

		LayerData& findWithInstance(IRendererAble* instance);

		void tick() override;
		void draw() override;

		Layers& operator=(const Layers& rhs);
		Layers& operator=(Layers&& rhs);

		std::vector<LayerData>& getLayerData();
	private:
		std::vector<LayerData> layerData;
	};
}