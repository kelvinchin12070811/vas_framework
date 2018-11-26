#pragma once
#if __has_include(<rapidjson/rapidjson.h>)
#include <fstream>
#include <stack>
#include <sstream>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include "NBTSerializer.hpp"

namespace vas
{
	class JsonDeserializer : public NBTSerializer
	{
	public:
		JsonDeserializer();
		explicit JsonDeserializer(std::ostringstream data);
		explicit JsonDeserializer(std::ifstream input);
		explicit JsonDeserializer(const std::string& fileName);
		~JsonDeserializer();

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