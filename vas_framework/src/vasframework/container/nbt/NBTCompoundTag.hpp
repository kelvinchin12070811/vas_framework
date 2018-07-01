#pragma once
#include <memory>
#include <string>
#include <map>
#include "ITag.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC NBTCompoundTag : public ITag
	{
	public:
		NBTCompoundTag();
		~NBTCompoundTag();

		std::shared_ptr<ITag> at(const std::string& name);
		bool insert(const std::string& name, const std::shared_ptr<ITag>& tag);
		bool insert(const std::string& name, std::shared_ptr<ITag>&& tag);
	public: //Getters
		std::map<std::string, std::shared_ptr<ITag>>& getTags();

	private:
		std::map<std::string, std::shared_ptr<ITag>> tags;
	};
}