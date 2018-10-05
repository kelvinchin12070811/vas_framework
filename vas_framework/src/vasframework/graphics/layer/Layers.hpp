#pragma once
#include <vector>
#include <boost/container/vector.hpp>
#include <memory>
#include <string>
#include "../DrawAble.hpp"
#include "../../VASConfig.hpp"

#define VAS_INSERT_VAR(var) vas::make_layerData(std::string(#var), var)
#define VAS_LAYER_DATA(name, var) vas::make_layerData(name, var)

namespace vas
{
	/** @addtogroup layers
		  @{
	*/
	/** @brief The container of the DrawAble objects in vertical order.
	*/
	class VAS_DECLSPEC Layers : public DrawAble
	{ /** @} */
	public:
		/** The direction of the shifting of the other objects. */
		enum class ShiftDirection : uint8_t {
			up /**< Shift upward. */
			, down /**< Shift downward. */
		};
		
		/** @brief Structure of the information of the layer's DrawAble object.
			  
			  A data type of vas::Layers

			  Creation of this sturcture can be done by using these helper functions and macros:
			  
			  Functions:
			   - make_layerData()

			  Macros:
			   - #VAS_INSERT_VAR
			   - #VAS_LAYER_DATA
		*/
		struct LayerData
		{
			bool visible; /**< Determine if the object is going to render on the renderer or not. */
			std::string name; /**< Name of the object. Unique id are recomanded. */
			std::shared_ptr<DrawAble> instance; /**< Shared instance of the object. */
		};
	public:
		Layers();
		Layers(const Layers& rhs);
		Layers(Layers&& rhs);
		~Layers();

		/** Insert new instance of DrawAble into the list.
			  @param data LayerData of the object.
			  @param pos Position hint to insert the object, insert at the back if maximum of size_t.
		*/
		void insert(const LayerData& data, size_t pos = SIZE_MAX);
		/** Insert new instance of DrawAble into the list.
			  @param data LayerData of the object.
			  @param pos Position hint to insert the object, insert at the back if maximum of size_t.
		*/
		void insert(LayerData&& data, size_t pos = SIZE_MAX);
		
		/** Remove the last object. */
		void remove();
		/** Remove the object by given name.
			  @param name Name of the object.
		*/
		void remove(const std::string& name);
		/** Remove the object by given index.
			  @param index Index of the object.
		*/
		void remove(size_t index);

		/** Shift the object by given index.
			  @param index Index of the object.
			  @param direction Direction of the shifting.
			  @param count Distance of the new index from current.
			  @return New index of the object.
		*/
		size_t shift(size_t index, Layers::ShiftDirection direction, size_t count);

		/** Clear the layer. */
		void clear();
		/** Count of objects stored in the layer. */
		size_t size();
		/** Check if the layer is empty.
			  @retval true if is empty.
		*/
		bool isEmpty();

		/** @name Iterators
			  @{
		*/
		std::vector<Layers::LayerData>::iterator begin(); /**< begin of the iterator. */
		std::vector<Layers::LayerData>::iterator end(); /**< end of the iterator. */
		std::vector<Layers::LayerData>::reverse_iterator rbegin(); /**< rbegin of the iterator. */
		std::vector<Layers::LayerData>::reverse_iterator rend(); /**< rend of the iterator. */
		/** @} */

		/** Get the object at given index.
			  @param index Index of the object.
			  @return LayerData of the object.
		*/
		LayerData& get(size_t index);
		/** Get the object at given name.
			  @param name Name of the object.
			  @return LayerData of the object.
		*/
		LayerData& get(const std::string& name);

		/** Find the object with an instance of it.
			  @param instance Raw pointer(observation pointer) to the object.
			  @return LayerData of the object.
		*/
		LayerData& findWithInstance(DrawAble* instance);

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

		Layers& operator=(const Layers& rhs);
		Layers& operator=(Layers&& rhs);

		std::vector<LayerData>& getLayerData();
	private:
		/** [Read Only] Object list of the layer.
			   - __accessors__
					 -# std::vector<LayerData>& getLayerData()
		*/
		std::vector<LayerData> layerData;
		boost::container::vector<bool> layerState;
	};

	/** @addtogroup layers
		  @{
	*/
	/** Create a new layer data.
		  @param name Name of the object.
		  @param instance Instance of the DrawAble object.
		  @param visible Define if the instance need to draw on the renderer or not.
		  @return Layers::LayerData that contain the information about the object.

		  Defined in: vasframework/graphics/layer/Layers.hpp, namespace: vas
	*/
	VAS_DECLSPEC Layers::LayerData make_layerData(const std::string& name, const std::shared_ptr<DrawAble>& instance, bool visible = true);
	/** Create a new layer data.
		  @param name Name of the object.
		  @param instance Rvalue refrence to the instance of the DrawAble object.
		  @param visible Define if the instance need to draw on the renderer or not.
		  @return Layers::LayerData that contain the information about the object.
		  
		  Defined in: vasframework/graphics/layer/Layers.hpp, namespace: vas
	*/
	VAS_DECLSPEC Layers::LayerData make_layerData(const std::string& name, std::shared_ptr<DrawAble>&& instance, bool visible = true);
	/** @} */
}