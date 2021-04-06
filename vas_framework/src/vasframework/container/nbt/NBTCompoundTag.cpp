//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include <iterator>
#include "NBTCompoundTag.hpp"

namespace vas
{
	NBTCompoundTag::NBTCompoundTag(std::initializer_list<std::pair<std::string, std::shared_ptr<ITag>>> list)
	{
		std::copy(list.begin(), list.end(), std::inserter(tags, tags.begin()));
	}

	std::unique_ptr<NBTCompoundTag> NBTCompoundTag::create()
	{
		return std::make_unique<NBTCompoundTag>();
	}

	std::unique_ptr<NBTCompoundTag> NBTCompoundTag::create(std::initializer_list<std::pair<std::string, std::shared_ptr<ITag>>> list)
	{
		return std::make_unique<NBTCompoundTag>(list.begin(), list.end());
	}

	std::shared_ptr<ITag> NBTCompoundTag::at(const std::string & name)
	{
		auto result = tags.find(name);
		return result == tags.end() ? nullptr : result->second;
	}

	bool NBTCompoundTag::insert(const std::string & name, const std::shared_ptr<ITag>& tag)
	{
		auto result = tags.insert({ name, tag });
		return result.second;
	}

	bool NBTCompoundTag::insert(const std::string & name, std::shared_ptr<ITag>&& tag)
	{
		auto result = tags.insert({ name, std::move(tag) });
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