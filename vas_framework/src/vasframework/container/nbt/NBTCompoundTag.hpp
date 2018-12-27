#pragma once
#include <initializer_list>
#include <memory>
#include <string>
#include <map>
#include "ITag.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/** @addtogroup nbt_tag
		  @{
	*/
	/** @brief The tree like structure that holds other ITag instances.
		  
		  The NBTCompoundTag class is a tree like structrue to contain other ITag's child including it self. This class provide
		  map like search functions and insert functions. This tag identify each ITag with a unique name assigend by user.
	*/
	class VAS_DECLSPEC NBTCompoundTag : public ITag
	{ /** @} */
	public:
		NBTCompoundTag() = default;
		/** Initialize NBTCompoundTag with iterator.
			  @param begin begin hint of iterator.
			  @param end end hint of iterator.
		*/
		template <class Iterator>
		NBTCompoundTag(Iterator begin, Iterator end)
		{
			std::copy(begin, end, std::inserter(tags, tags.begin()));
		}
		/** Initialize CompoundTag with initializer_list. */
		NBTCompoundTag(std::initializer_list<std::pair<std::string, std::shared_ptr<ITag>>> list);

		/** Create new instance of tag, use with list initialization.
			  @retval std::unique_ptr<NBTCompoundTag> new instance of tag.
		*/
		static std::unique_ptr<NBTCompoundTag> create();
		/** Create new instance of tag, use with list initialization.
			  @param list value to initializes the tag.
			  @retval std::unique_ptr<NBTCompoundTag> new instance of tag.
		*/
		static std::unique_ptr<NBTCompoundTag> create(std::initializer_list<std::pair<std::string, std::shared_ptr<ITag>>> list);
		/** Find a NBT tag with it's name. std::out_of_range thrown if failed.
			  @param name Name of the NBT tag.
		*/
		std::shared_ptr<ITag> at(const std::string& name);
		/** Insert a NBT tag into the compound tag.
			  @param name Name of the tag.
			  @param tag Instance of the tag.
			  @return true if success.
		*/
		bool insert(const std::string& name, const std::shared_ptr<ITag>& tag);
		/** Insert a NBT tag into the compound tag.
			  @param name Name of the tag.
			  @param tag Rvalue instance of the tag.
			  @return true if success.
		*/
		bool insert(const std::string& name, std::shared_ptr<ITag>&& tag);
		void serialize(const std::string& name, NBTSerializer& serializer) override;
	public: //Getters
		std::map<std::string, std::shared_ptr<ITag>>& getTags();

	private:
		/** [Read Only] Tags mapped.
			  - __accessors__
				-# std::map<std::string, std::shared_ptr<ITag>>& getTags()
		*/
		std::map<std::string, std::shared_ptr<ITag>> tags;
	};
}