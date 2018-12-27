#include <boost/lexical_cast.hpp>
#include <rapidjson/error/en.h>
#include "JsonDeserializer.hpp"
#include "../../util/FileUtil.hpp"

#if __has_include(<rapidjson/rapidjson.h>)

namespace vas
{
	JsonDeserializer::JsonDeserializer(std::ostringstream data)
	{
		rapidjson::ParseResult result = doc.Parse(data.str().c_str());
		if (result.IsError())
		{
			std::string jsonStr{ data.str() };
			jsonStr.insert(result.Offset(), "->");
			throw std::runtime_error{ "JSON parsing error at offset " + boost::lexical_cast<std::string>(result.Offset())
				+ ": " + rapidjson::GetParseError_En(result.Code()) + "\n\n" + jsonStr };
		}
	}

	JsonDeserializer::JsonDeserializer(std::ifstream input)
	{
		std::string ss{ readAll(input).str() };
		rapidjson::ParseResult result = doc.Parse(ss.c_str());
		if (result)
		{
			std::string jsonStr = ss;
			jsonStr.insert(result.Offset(), "->");
			throw std::runtime_error{ "JSON parsing error at offset " + boost::lexical_cast<std::string>(result.Offset()) + ": " +
				rapidjson::GetParseError_En(result.Code()) + "\n\n" + jsonStr };
		}
	}

	JsonDeserializer::JsonDeserializer(const std::string & fileName)
	{
		std::string ss{ readAll(fileName).str() };
		if (ss.empty()) throw std::runtime_error{ "Unable to open file \"" + fileName + "\"." };

		rapidjson::ParseResult result = doc.Parse(ss.c_str());
		if (result)
		{
			std::string jsonStr = ss.c_str();
			jsonStr.insert(result.Offset(), "->");
			throw std::runtime_error{ "JSON parsing error at offset " + boost::lexical_cast<std::string>(result.Offset()) + ": " +
				rapidjson::GetParseError_En(result.Code()) + "\n\n" + jsonStr };
		}
	}

	JsonDeserializer::JsonDeserializer(rapidjson::Document document):
		doc(std::move(document))
	{
	}

	void JsonDeserializer::treeStart(const std::string & name)
	{
		if (stackTrace.empty())
		{
			if (!doc.HasMember(name.c_str()))
				throw std::logic_error{ "The JSON document does not contain child \"" + name + "\"." };
			stackTrace.push({ name, &doc[name.c_str()] });
		}
		else
		{
			auto top = stackTrace.top();
			if (!top.second->HasMember(name.c_str()))
				throw std::logic_error{ "The element \"" + top.first + "\" does not contain child \"" + name + "\"." };
			stackTrace.push({ name, &(*top.second)[name.c_str()] });
		}
	}

	void JsonDeserializer::treeEnd()
	{
		if (!stackTrace.empty())
			stackTrace.pop();
	}
	
	void JsonDeserializer::arrayStart(const std::string & name)
	{
		treeStart(name);
	}
	
	void JsonDeserializer::arrayEnd()
	{
		treeEnd();
	}

	void JsonDeserializer::arraySizeSetter(NBTSerializer::ArraySizeSetter setter)
	{
		auto top = stackTrace.top();
		if (!top.second->IsArray())
			throw std::logic_error{ "The element \"" + top.first + "\" is not an array." };
		if (setter != nullptr) setter(top.second->GetArray().Size());
	}

	void JsonDeserializer::accept(const std::string & name, std::byte & value)
	{
		auto& result = get(name);
		if (!result.IsInt())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid byte (int32_t) type." };
		value = static_cast<std::byte>(result.GetInt());
	}

	void JsonDeserializer::accept(const std::string & name, std::int16_t & value)
	{
		auto& result = get(name);
		if (!result.IsInt())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid int16 (int32_t) type." };
		value = static_cast<std::int16_t>(result.GetInt());
	}

	void JsonDeserializer::accept(const std::string & name, std::int32_t & value)
	{
		auto& result = get(name);
		if (!result.IsInt())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid int32 type." };
		value = result.GetInt();
	}

	void JsonDeserializer::accept(const std::string & name, std::uint32_t & value)
	{
		auto& result = get(name);
		if (!result.IsUint())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid uint32 type." };
		value = result.GetUint();
	}

	void JsonDeserializer::accept(const std::string & name, std::int64_t & value)
	{
		auto& result = get(name);
		if (!result.IsInt64())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid int64 type." };
		value = result.GetInt64();
	}

	void JsonDeserializer::accept(const std::string & name, std::uint64_t & value)
	{
		auto& result = get(name);
		if (!result.IsUint())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid uint64 type." };
		value = result.GetUint64();
	}

	void JsonDeserializer::accept(const std::string & name, float & value)
	{
		auto& result = get(name);
		if (!result.IsFloat())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid float type." };
		value = result.GetFloat();
	}

	void JsonDeserializer::accept(const std::string & name, double & value)
	{
		auto& result = get(name);
		if (!result.IsDouble())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid double type." };
		value = result.GetDouble();
	}

	void JsonDeserializer::accept(const std::string & name, bool & value)
	{
		auto& result = get(name);
		if (!result.IsBool())
			throw std::logic_error{ "The element \"" + name + "\" is not a valid bool type." };
		value = result.GetBool();
	}

	void JsonDeserializer::accept(const std::string & name, std::string & value)
	{
		auto& result = get(name);
		if (!result.IsString())
			throw std::logic_error{ "Element \"" + name + "\" is not a string." };
		value = { result.GetString(), result.GetStringLength() };
	}

	rapidjson::Value & JsonDeserializer::get(const std::string & name)
	{
		if (stackTrace.empty())
		{
			if (!doc.IsObject()) throw std::logic_error{ "The root of the tree is not object type" };

			if (!doc.HasMember(name.c_str()))
				throw std::runtime_error{ "Unable to find the member \"" + name + "\"." };
			return doc[name.c_str()];
		}
		else
		{
			auto top = stackTrace.top();
			if (top.second->IsObject())
			{
				top.second->HasMember(name.c_str());
				return (*top.second)[name.c_str()];
			}
			else if (top.second->IsArray())
			{
				return (*top.second)[boost::lexical_cast<size_t>(name)];
			}
			else
			{
				throw std::logic_error{ "The element \"" + top.first + "\" is not an array or object." };
			}
		}
	}
}
#endif // __has_include(<rapidjson/rapidjson.h>)