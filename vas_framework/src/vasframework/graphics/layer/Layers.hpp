//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <vector>
#include <boost/container/vector.hpp>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include "../DrawAble.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup g_layers
	 * @{
	 */
	/**
	 * @brief The container of the DrawAble objects in vertical order.
	 */
	class VAS_DECLSPEC Layer : public DrawAble
	{ /** @} */
	public:
		/** The direction of the shifting of the other objects. */
		enum class ShiftDirection : uint8_t {
			up /**< Shift upward. */
			, down /**< Shift downward. */
		};
		
		/**
		 * @brief Structure of the information of the layer's DrawAble object.
		 * 
		 * A data type of vas::Layer
		 * 
		 * Creation of this sturcture can be done by using these helper functions and macros:
		 * 
		 * Functions:
		 * - make_layerData()
		 */
		struct LayerData
		{
			/**
			 * Construct new instance
			 * @param[in] instance Instance of DrawAble object.
			 * @param[in] visible Determin if the object is visible 
			 */
			LayerData(std::shared_ptr<DrawAble> instance, bool visible = true);
			bool visible; /**< Determine if the object is going to render on the renderer or not. */
			std::shared_ptr<DrawAble> instance; /**< Shared instance of the object. */
		};
	public:
		Layer();
		Layer(const Layer& rhs);
		Layer(Layer&& rhs) noexcept;
		~Layer() = default;

		/**
		 * Insert new instance of DrawAble into the list.
		 * @param[in] data LayerData of the object.
		 * @param[in] pos Position hint to insert the object, insert at the back if maximum of size_t.
		 */
		LayerData& insert(LayerData data, size_t pos = (std::numeric_limits<size_t>::max)());
		/**
		 * Create and insert new instance of DrawAble object into the list.
		 * @tparam GenericDrawAbleObj DrawAble objects' type.
		 * @tparam Args Variadic parameters type.
		 * @param args Parameters that forward to the constructor of the GenericDrawAbleObj.
		 * @retval std::pair of reference to LayerData(first) and convertion function to std::shared_ptr(second).
		 */
		template <class GenericDrawAbleObj, class... Args>
		std::pair<LayerData&, std::function<std::shared_ptr<GenericDrawAbleObj>()>> emplaceInsert(Args&&... args)
		{
			auto& result = this->insert({ std::make_shared<GenericDrawAbleObj>(std::forward<Args>(args)...) });
			return { result, [&]() { return std::static_pointer_cast<GenericDrawAbleObj>(result.instance); } };
		}
		
		/** Remove the last object. */
		void remove();
		/**
		 * Remove the object by given instance.
		 * @param[in] instance Instance of the object.
		 */
		void remove(const DrawAble* instance);
		/**
		 * Remove the object by given index.
		 * @param[in] index Index of the object.
		 */
		void remove(size_t index);

		/**
		 * Shift the object by given index.
		 * @param[in] index Index of the object.
		 * @param[in] direction Direction of the shifting.
		 * @param[in] count Distance of the new index from current.
		 * @return New index of the object.
		 * @throw std::logic_error if @p index is larger than length of the array.
		 */
		size_t shift(size_t index, Layer::ShiftDirection direction, size_t count);

		/** Clear the layer. */
		void clear();
		/** Count of objects stored in the layer. */
		size_t size();
		/**
		 * Check if the layer is empty.
		 * @retval true if is empty.
		 */
		bool isEmpty();

		void forceGC(); /**< Force reduce layer size to prefered buffer size. */
		void shrinkToFit(); /**< Shrink layer size to fit with the objects stored. */

		/**
		 * @name Iterators
		 * @{
		 */
		std::vector<Layer::LayerData>::iterator begin(); /**< begin of the iterator. */
		std::vector<Layer::LayerData>::iterator end(); /**< end of the iterator. */
		std::vector<Layer::LayerData>::reverse_iterator rbegin(); /**< rbegin of the iterator. */
		std::vector<Layer::LayerData>::reverse_iterator rend(); /**< rend of the iterator. */
		/** @} */

		/**
		 * Get the object at given index.
		 * @param[in] index Index of the object.
		 * @return LayerData of the object.
		 * @throw std::logic_error if @p index is larger than array length.
		 */
		LayerData& get(size_t index);
		/**
		 * Get the object with an instance of it.
		 * @param[in] instance Raw pointer(observation pointer) to the object.
		 * @return LayerData of the object.
		 * @throw std::logic_error if @p instance not found in array.
		 */
		LayerData& get(DrawAble* instance);
		/**
		 * Get the index of the object with an instance of it.
		 * @param[in] instance Instance of object to search.
		 */
		std::optional<size_t> indexOf(DrawAble* instance);

		static void setAutoGC(bool value);
		static void setMinLayerCount(size_t value);

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

		Layer& operator=(const Layer& rhs);
		Layer& operator=(Layer&& rhs) noexcept;

		std::vector<LayerData>& getLayerData();
	private:
		/**
		 * Object list of the layer.
		 * ####Accessors
		 * -# std::vector<LayerData>& getLayerData()
		 */
		std::vector<LayerData> layerData;
		/**
		 * Determin if the layer will auto release free memory.
		 * ####Mutators
		 * -# static void setAutoGC(bool value)
		 */
		static bool autoGC;
		/**
		 * Determin the minimum number of layers that can be stored without reallocate memory.
		 * ####Mutators
		 * -# static void setMinLayerCount(size_t value)
		 */
		static size_t minLayerCount;
	};
}