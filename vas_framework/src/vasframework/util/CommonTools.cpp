#include "CommonTools.hpp"


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
		TextTools::printfln(boost::format("%s: %s") % this->assistanceName % message);
		
		if (messType != CommonTools::MessageType::log && messType != CommonTools::MessageType::info)
		{
#ifdef VAS_WINDOWS_MODE
			MessageBeep(static_cast<UINT>(messType));
			MessageBox(windowInstance, TextTools::stows(message).c_str(), TextTools::stows(assistanceName).c_str(), static_cast<UINT>(messType));
#else
			SDL_MessageBoxFlags flags;
			if (messType == CommonTools::MessageType::error)
				flags = SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR;
			else if (messType == CommonTools::MessageType::warning)
				flags = SDL_MessageBoxFlags::SDL_MESSAGEBOX_INFORMATION;

			SDL_ShowSimpleMessageBox(flags, this->assistanceName.c_str(), message.c_str(), static_cast<SDL_Window*>(windowInstance));
#endif // VAS_WINDOWS_MODE
		}
		return rtnValue;
	}

	int CommonTools::messenger(const std::ostream & message, CommonTools::MessageType messType, int rtnValue)
	{
		return messenger(static_cast<const std::stringstream&>(message).str(), messType, rtnValue);
	}

	int CommonTools::messenger(const boost::format& message, CommonTools::MessageType messType, int rtnValue)
	{
		return messenger(message.str(), messType, rtnValue);
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

	Log & Log::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}

	Err & Err::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}

	Info & Info::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}

	Warn & Warn::operator<<(std::ostream &(*manipulator)(std::ostream &o))
	{
		ss << manipulator;
		return *this;
	}
}