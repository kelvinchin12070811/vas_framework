#pragma once
#include <vector>
#include "AbstractMapLayer.hpp"
#include "../container/ObjectData.hpp"

namespace vas
{
	class VAS_DECLSPEC ObjectLayer : public AbstractMapLayer
	{
	public:
		ObjectLayer();
		~ObjectLayer();

	public: // Setters
		void setObjectList(std::vector<ObjectData>&& value);
	public: // Getters
		const std::vector<ObjectData>& getObjectList() const;

	private:
		std::vector<ObjectData> objectList;
	};
}