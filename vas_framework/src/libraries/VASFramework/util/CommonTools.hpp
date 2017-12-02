#pragma once
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <vector>

namespace vas
{
	class CommonTools
	{
	public:
		static CommonTools& getInstance();
		enum class Messtype { showOnly = -1, informationNoPromp = -2, information = MB_ICONINFORMATION, warning = MB_ICONWARNING, error = MB_ICONERROR};
		void setAssistanceName(const std::wstring& name);

		const std::wstring& getAssistanceName();

		int messenger(const std::wstring& message, Messtype type = Messtype::showOnly, int returnValue = 0);

		void createConsole();
		void freeConsole();

		HWND __window_hwnd = nullptr;
		bool __logging = false;
		std::vector<std::wstring> __logs;
	private:
		CommonTools();
		~CommonTools();

#ifdef _WINDOWS
		bool haveConsole = false;
#else
		bool haveConsole = true;
#endif // _WINDOWS

		
		std::wstring assistanceName;
	};
	inline CommonTools& CommonToolsAPI() { return CommonTools::getInstance(); };
}