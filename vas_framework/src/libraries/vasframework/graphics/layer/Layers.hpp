#pragma once
#include <vector>
#include <boost/container/vector.hpp>
#include <memory>
#include <string>
#include "../IRenderAble.hpp"
#include "../../VASConfig.hpp"

#define VAS_INSERT_VAR(var) vas::make_layerData(std::string(#var), var)
#define VAS_LAYER_DATA(name, var) vas::make_layerData(name, var)

namespace vas
{
	class VAS_DECLSPEC Layers : public IRenderAble
	{
	public:
		enum class ShiftDirection : uint8_t { up, down };
		//using LayerData = std::pair<std::string, std::shared_ptr<IRenderAble>>;
		struct LayerData
		{
			bool visible;
			std::string name;
			std::shared_ptr<IRenderAble> instance;
		};
	public:
		Layers();
		Layers(const Layers& rhs);
		Layers(Layers&& rhs);
		~Layers();

		void insert(const LayerData& data, size_t pos = SIZE_MAX);
		void insert(LayerData&& data, size_t pos = SIZE_MAX);
		
		void remove();
		void remove(const std::string& name);
		void remove(size_t index);

		size_t shift(size_t index, Layers::ShiftDirection direction, size_t count);

		void clear();
		size_t size();
		bool isEmpty();

		std::vector<Layers::LayerData>::iterator begin();
		std::vector<Layers::LayerData>::iterator end();
		std::vector<Layers::LayerData>::reverse_iterator rbegin();
		std::vector<Layers::LayerData>::reverse_iterator rend();

		LayerData& get(size_t index);
		LayerData& get(const std::string& name);

		LayerData& findWithInstance(IRenderAble* instance);

		void tick() override;
		void draw() override;

		Layers& operator=(const Layers& rhs);
		Layers& operator=(Layers&& rhs);

		std::vector<LayerData>& getLayerData();
	private:
		std::vector<LayerData> layerData;
		boost::container::vector<bool> layerState;
	};

	VAS_DECLSPEC Layers::LayerData make_layerData(const std::string& name, const std::shared_ptr<IRenderAble>& instance, bool visible = true);
	VAS_DECLSPEC Layers::LayerData make_layerData(const std::string& name, std::shared_ptr<IRenderAble>&& instance, bool visible = true);
}