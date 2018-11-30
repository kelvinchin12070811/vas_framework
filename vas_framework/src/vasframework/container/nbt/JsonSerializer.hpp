#pragma once
#if __has_include(<rapidjson/rapidjson.h>) || defined(DOXYGEN)
#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <sstream>
#include <stack>
#include "NBTSerializer.hpp"

namespace vas
{
	/** @addtogroup nbt_tag
		  @{
	*/
	/** @brief Json serialization engine for NBT Tags.

		  The JsonSerializer serialize the NBT tags into json document. This class required rapidjson library.
	*/
	class JsonSerializer : public NBTSerializer
	{ /** @} */
	public:
		JsonSerializer();
		~JsonSerializer() = default;

		void treeStart(const std::string& name) override;
		void treeEnd() override;
		void arrayStart(const std::string& name) override;
		void arrayEnd() override;
		void arraySizeSetter(NBTSerializer::ArraySizeSetter setter) override;

		rapidjson::Document& getDocument();
		const rapidjson::Document& getDocument() const;

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

		std::string getJSON() const; /**< Get the JSON string. */
	private:
		void append(const std::string& name, rapidjson::Value&& value);
	private:
		/** [Read & Write] JSON document of the serialized json.
				- __accessors__
					-# rapidjson::Document& getDocument()
					-# const rapidjson::Document& getDocument() const
		*/
		rapidjson::Document document;
		std::stack<std::pair<std::string, rapidjson::Value>> stackTrace;
	};
}
#endif