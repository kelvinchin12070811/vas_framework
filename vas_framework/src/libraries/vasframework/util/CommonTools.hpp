#pragma once
#include <string>
#include <functional>

namespace vas
{
	class CommonTools
	{
	public:
		enum class MessageType : long
		{
			log = -1,
			info,
			warning = 0x00000040L,
			error = 0x00000010L
		};
		static CommonTools& getInstance();
	
		bool hasConsole{ false };

		int messenger(
			const std::string& message,
			CommonTools::MessageType messType = CommonTools::MessageType::log,
			int rtnValue = 0
		);

		void setAssistanceName(const std::string& value);
		std::string getAssistanceName();

		std::function<void(const std::string&, CommonTools::MessageType, int)>& Loggingfunction();
	private:
		CommonTools();
		~CommonTools();

		std::string assistanceName;
		std::function<void(const std::string&, CommonTools::MessageType, int)> loggingFunction = nullptr;
	};
}