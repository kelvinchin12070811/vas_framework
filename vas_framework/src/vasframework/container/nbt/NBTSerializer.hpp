#pragma once
#include <boost/assert.hpp>
#include <functional>
#include <string>

namespace vas
{
	class NBTSerializer
	{
	public:
		using ArraySizeSetter = std::function<void(size_t)>;
	public:
		virtual ~NBTSerializer() = 0{}
		virtual void treeStart(const std::string& name) = 0;
		virtual void treeEnd() = 0;
		virtual void arrayStart(const std::string& name) = 0;
		virtual void arrayEnd() = 0;
		virtual void arraySizeSetter(ArraySizeSetter setter) = 0;

		virtual void accept(const std::string& name, std::byte& value) = 0;
		virtual void accept(const std::string& name, std::int16_t& value) = 0;
		virtual void accept(const std::string& name, std::int32_t& value) = 0;
		virtual void accept(const std::string& name, std::uint32_t& value) = 0;
		virtual void accept(const std::string& name, std::int64_t& value) = 0;
		virtual void accept(const std::string& name, std::uint64_t& value) = 0;
		virtual void accept(const std::string& name, float& value) = 0;
		virtual void accept(const std::string& name, double& value) = 0;
		virtual void accept(const std::string& name, bool& value) = 0;
		virtual void accept(const std::string& name, std::string& value) = 0;
	};
}