#if __has_include(<rapidjson/rapidjson.h>)
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include "JsonSerializer.hpp"

namespace vas
{
	JsonSerializer::JsonSerializer()
	{
		document.SetObject();
	}

	void JsonSerializer::treeStart(const std::string & name)
	{
		rapidjson::Value tree;
		tree.SetObject();
		stackTrace.push({ name, std::move(tree) });
	}

	void JsonSerializer::treeEnd()
	{
		if (!stackTrace.empty())
		{
			auto tree = std::move(stackTrace.top());
			stackTrace.pop();
			append(tree.first, std::move(tree.second));
		}
	}

	void JsonSerializer::arrayStart(const std::string & name)
	{
		rapidjson::Value list{ rapidjson::kArrayType };
		stackTrace.push({ name, std::move(list) });
	}

	void JsonSerializer::arrayEnd()
	{
		if (!stackTrace.empty())
		{
			auto list = std::move(stackTrace.top());
			stackTrace.pop();
			append(list.first, std::move(list.second));
		}
	}

	void JsonSerializer::arraySizeSetter(NBTSerializer::ArraySizeSetter setter)
	{
		return;
	}

	rapidjson::Document & JsonSerializer::getDocument()
	{
		return const_cast<rapidjson::Document&>(const_cast<const JsonSerializer*>(this)->getDocument());
	}

	const rapidjson::Document & JsonSerializer::getDocument() const
	{
		return document;
	}

	void JsonSerializer::accept(const std::string & name, std::byte & value)
	{
		rapidjson::Value tmp{ rapidjson::kNumberType };
		tmp = static_cast<std::int32_t>(value);
		append(name, std::move(tmp));
	}

	void JsonSerializer::accept(const std::string & name, std::int16_t & value)
	{
		rapidjson::Value tmp{ rapidjson::kNumberType };
		tmp = static_cast<std::int32_t>(value);
		append(name, std::move(tmp));
	}

	void JsonSerializer::accept(const std::string & name, std::int32_t & value)
	{
		rapidjson::Value tmp{ rapidjson::kNumberType };
		tmp = value;
		append(name, std::move(tmp));
	}

	void JsonSerializer::accept(const std::string & name, std::uint32_t & value)
	{
		rapidjson::Value tmp{ rapidjson::kNumberType };
		tmp = value;
		append(name, std::move(tmp));
	}
	void JsonSerializer::accept(const std::string & name, std::int64_t & value)
	{
		rapidjson::Value tmp{ rapidjson::kNumberType };
		tmp = value;
		append(name, std::move(tmp));
	}

	void JsonSerializer::accept(const std::string & name, std::uint64_t & value)
	{
		rapidjson::Value tmp{ rapidjson::kNumberType };
		tmp = value;
		append(name, std::move(tmp));
	}

	void JsonSerializer::accept(const std::string & name, float & value)
	{
		rapidjson::Value tmp{ rapidjson::kNumberType };
		tmp = value;
		append(name, std::move(tmp));
	}

	void JsonSerializer::accept(const std::string & name, double & value)
	{
		rapidjson::Value tmp{ rapidjson::kNumberType };
		tmp = value;
		append(name, std::move(tmp));
	}

	void JsonSerializer::accept(const std::string & name, bool & value)
	{
		rapidjson::Value tmp;
		tmp.SetBool(value);
		append(name, std::move(tmp));
	}

	void JsonSerializer::accept(const std::string & name, std::string & value)
	{
		rapidjson::Value tmp{ rapidjson::kStringType };
		tmp = rapidjson::StringRef(value.c_str());
		append(name, std::move(tmp));
	}

	std::string JsonSerializer::getJSON() const
	{
		rapidjson::StringBuffer buffer;
		rapidjson::PrettyWriter<decltype(buffer)> writer{ buffer };
		document.Accept(writer);
		return buffer.GetString();
	}

	void JsonSerializer::append(const std::string& name, rapidjson::Value && value)
	{
		if (stackTrace.empty())
		{
			document.AddMember({ name.c_str(), name.length(), document.GetAllocator() },
				std::move(value), document.GetAllocator());
		}
		else
		{
			auto& topItm = stackTrace.top();
			if (topItm.second.IsArray())
			{
				topItm.second.PushBack(value, document.GetAllocator());
			}
			else
			{
				stackTrace.top().second.AddMember({ name.c_str(), name.length(), document.GetAllocator() },
					std::move(value), document.GetAllocator());
			}
		}
	}
}
#endif