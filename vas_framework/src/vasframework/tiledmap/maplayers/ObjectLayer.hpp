#pragma once
#include <vector>
#include "AbstractMapLayer.hpp"
#include "../container/ObjectData.hpp"

namespace vas
{
	/** @addtogroup tile_codec
		  @{
	*/
	/** @brief The layer of objects. */
	class VAS_DECLSPEC ObjectLayer : public AbstractMapLayer
	{ /** @} */
	public:
		ObjectLayer();
		~ObjectLayer();

	public: // Setters
		void setObjectList(std::vector<ObjectData>&& value);
	public: // Getters
		const std::vector<ObjectData>& getObjectList() const;

	private:
		/** [Read & Write] The list of the objects.\n
				- __mutators__
					-# void setObjectList(std::vector<ObjectData>&& value)
				- __accessors__
					-# const std::vector<ObjectData>& getObjectList() const
		*/
		std::vector<ObjectData> objectList;
	};
}