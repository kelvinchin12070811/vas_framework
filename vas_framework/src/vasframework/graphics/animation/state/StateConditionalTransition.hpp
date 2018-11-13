#pragma once
#include <any>
#include <functional>
#include <string>

namespace vas
{
	template <typename T, typename Predicate = std::equal_to>
	bool anyCompare(const std::any& value, const T& compare)
	{
		if (!value.has_value())
			return false;

		if (value.type() == typeid(T))
		{
			Predicate pre;
			return pre(std::any_cast<T>(value), compare);
		}
		return false
	}

	class StateConditionalTransition
	{
	public:
		StateConditionalTransition(const std::string& srcState, const std::string& destState, std::function<bool(const std::any&)> validator);
		~StateConditionalTransition();
		bool achieved(const std::any& cdVar) const;

		std::string getSrcState() const;
		std::string getDestState() const;
	private:
		std::string srcState;
		std::string destState;
		std::function<bool(const std::any&)> validator;
	};
}