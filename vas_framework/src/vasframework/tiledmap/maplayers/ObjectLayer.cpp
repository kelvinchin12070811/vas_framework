#include "ObjectLayer.hpp"

namespace vas
{
	ObjectLayer::ObjectLayer()
	{
	}

	ObjectLayer::~ObjectLayer()
	{
	}

	void ObjectLayer::setObjectList(std::vector<ObjectData>&& value)
	{
		objectList = std::move(value);
	}

	const std::vector<ObjectData>& ObjectLayer::getObjectList() const
	{
		return objectList;
	}
}