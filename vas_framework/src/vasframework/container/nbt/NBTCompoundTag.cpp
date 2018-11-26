#include "NBTCompoundTag.hpp"

namespace vas
{
	NBTCompoundTag::NBTCompoundTag()
	{
	}

	NBTCompoundTag::~NBTCompoundTag()
	{
	}

	std::shared_ptr<ITag> NBTCompoundTag::at(const std::string & name)
	{
		auto result = tags.find(name);
		return result == tags.end() ? nullptr : result->second;
	}

	bool NBTCompoundTag::insert(const std::string & name, const std::shared_ptr<ITag>& tag)
	{
		auto result = tags.insert(std::make_pair(name, tag));
		return result.second;
	}

	bool NBTCompoundTag::insert(const std::string & name, std::shared_ptr<ITag>&& tag)
	{
		auto result = tags.insert(std::make_pair(name, std::move(tag)));
		return result.second;
	}

	void NBTCompoundTag::serialize(const std::string & name, NBTSerializer & serializer)
	{
		serializer.treeStart(name);
		for (auto itr = tags.begin(); itr != tags.end(); itr++)
			itr->second->serialize(itr->first, serializer);
		serializer.treeEnd();
	}

	std::map<std::string, std::shared_ptr<ITag>>& NBTCompoundTag::getTags()
	{
		return tags;
	}
}