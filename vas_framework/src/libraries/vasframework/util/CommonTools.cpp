#include "CommonTools.hpp"
#include "TextTools.hpp"

namespace vas
{
	CommonTools & CommonTools::getInstance()
	{
		static CommonTools instance;
		return instance;
	}

	int CommonTools::messenger(const std::string & message, CommonTools::MessageType messType, int rtnValue)
	{
		if (loggingFunction != nullptr) loggingFunction(message, messType, rtnValue);
		return rtnValue;
	}

	void CommonTools::setAssistanceName(const std::string & value)
	{
		this->assistanceName = value;
	}

	std::string CommonTools::getAssistanceName()
	{
		return assistanceName;
	}

	std::function<void(const std::string&, CommonTools::MessageType, int)>& CommonTools::Loggingfunction()
	{
		return loggingFunction;
	}

	CommonTools::CommonTools()
	{
	}

	CommonTools::~CommonTools()
	{
	}
}