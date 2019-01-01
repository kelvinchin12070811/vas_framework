//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#if __has_include(<rapidjson/rapidjson.h>) || defined(DOXYGEN)
#include <fstream>
#include <stack>
#include <sstream>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include "NBTSerializer.hpp"

namespace vas
{
	/** @addtogroup nbt_tag
		  @{
	*/
	/** @brief The JSON deserializer of the NBT tags.
		  
		  The deserializer that deserialize JSON to the NBT tree, only avaliable if rapidjson library found.
	*/
	class JsonDeserializer : public NBTSerializer
	{ /** @} */
	public:
		JsonDeserializer() = default;
		/** Construct from JSON data.
			  @param data JSON data to parse.
		*/
		explicit JsonDeserializer(std::ostringstream data);
		/** Consturct from loaded file
			  @param input Input file that contain JSON data.
		*/
		explicit JsonDeserializer(std::ifstream input);
		/** Construct by loading file.
			  @param fileName Name of the file to load.
		*/
		explicit JsonDeserializer(const std::string& fileName);
		/** Construct from JSON document.
			  @param document JSON document to load.
			  @note the @p document require user to move its ownership (uncopyable object).
		*/
		explicit JsonDeserializer(rapidjson::Document document);

		void treeStart(const std::string& name) override;
		void treeEnd() override;
		void arrayStart(const std::string& name) override;
		void arrayEnd() override;
		void arraySizeSetter(NBTSerializer::ArraySizeSetter setter) override;
		
		void accept(const std::string& name, std::byte& value) override;
		void accept(const std::string& name, std::int16_t& value) override;
		void accept(const std::string& name, std::int32_t& value) override;
		void accept(const std::string& name, std::uint32_t& value) override;
		void accept(const std::string& name, std::int64_t& value) override;
		void accept(const std::string& name, std::uint64_t& value) override;
		void accept(const std::string& name, float& value) override;
		void accept(const std::string& name, double& value) override;
		void accept(const std::string& name, bool& value) override;
		void accept(const std::string& name, std::string& value) override;
	private:
		rapidjson::Value& get(const std::string& name);
	private:
		rapidjson::Document doc;
		std::stack<std::pair<std::string, rapidjson::Value*>> stackTrace;
		rapidjson::Value::ValueIterator arrayItr;
	};
}
#endif // __has_include(<rapidjson/rapidjson.h>)