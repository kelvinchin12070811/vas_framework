//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#if __has_include(<rapidjson/rapidjson.h>) || defined(DOXYGEN)
#include <fstream>
#include <stack>
#include <sstream>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include "NBTSerializer.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup nbt_tag
	 * @{
	 */
	/**
	 * @brief The JSON deserializer of the NBT tags.
	 * 
	 * The deserializer that deserialize JSON to the NBT tree, only avaliable if rapidjson library found.
	 */
	class VAS_DECLSPEC JsonDeserializer : public NBTSerializer
	{ /** @} */
	public:
		JsonDeserializer() = default;
		/**
		 * Construct from JSON data.
		 * @param[in] data JSON data to parse.
		 * @throw std::runtime_error if has any json parsing error.
		 */
		explicit JsonDeserializer(std::ostringstream data);
		/**
		 * Consturct from loaded file
		 * @param[in] input Input file that contain JSON data.
		 * @throw std::runtime_error if has any json parsing error.
		 */
		explicit JsonDeserializer(std::ifstream input);
		/**
		 * Construct by loading file.
		 * @param[in] fileName Name of the file to load.
		 * @throw std::runtime_error if has any json parsing error.
		 */
		explicit JsonDeserializer(const std::string& fileName);
		/**
		 * Construct from JSON document.
		 * @param[in] document JSON document to load.
		 * @note the @p document require user to move its ownership (uncopyable object).
		 */
		explicit JsonDeserializer(rapidjson::Document document);

		void treeStart(const std::string& name) override; /**< @throw std::logic_error if current child has no child as @p name */
		void treeEnd() override;
		void arrayStart(const std::string& name) override;
		void arrayEnd() override;
		void arraySizeSetter(NBTSerializer::ArraySizeSetter setter) override; /**< @throw std::logic_error if current child is not an array */
		
		void accept(const std::string& name, std::byte& value) override; /**< @throw std::logic_error if datatype is not std::byte */
		void accept(const std::string& name, std::int16_t& value) override; /**< @throw std::logic_error if datatype is not std::int16_t */
		void accept(const std::string& name, std::int32_t& value) override; /**< @throw std::logic_error if datatype is not std::int32_t */
		void accept(const std::string& name, std::uint32_t& value) override; /**< @throw std::logic_error if datatype is not std::uint32_t */
		void accept(const std::string& name, std::int64_t& value) override; /**< @throw std::logic_error if datatype is not std::int64_t */
		void accept(const std::string& name, std::uint64_t& value) override; /**< @throw std::logic_error if datatype is not std::uint64_t */
		void accept(const std::string& name, float& value) override; /**< @throw std::logic_error if datatype is not float */
		void accept(const std::string& name, double& value) override; /**< @throw std::logic_error if datatype is not double */
		void accept(const std::string& name, bool& value) override; /**< @throw std::logic_error if datatype is not bool */
		void accept(const std::string& name, std::string& value) override; /**< @throw std::logic_error if datatype is not std::string */
	private:
		rapidjson::Value& get(const std::string& name);
	private:
		rapidjson::Document doc;
		std::stack<std::pair<std::string, rapidjson::Value*>> stackTrace;
		rapidjson::Value::ValueIterator arrayItr;
	};
}
#endif // __has_include(<rapidjson/rapidjson.h>)