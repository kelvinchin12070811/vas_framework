#include "CommonTools.hpp"
#include "../Base/Base.hpp"
#include <iostream>

namespace vas
{
	CommonTools & CommonTools::getInstance()
	{
		static CommonTools instance;
		return instance;
	}

	void CommonTools::setAssistanceName(const std::wstring & name)
	{
		if (assistanceName != name)
			assistanceName = name;
	}

	const std::wstring & CommonTools::getAssistanceName()
	{
		return assistanceName;
	}

	int CommonTools::messenger(const std::wstring & message, Messtype type, int returnValue)
	{
		if (__logging)
		{
			std::wstring typeName;
			switch (type)
			{
			case Messtype::showOnly:
				typeName = L"[cout]";
				break;
			case Messtype::error:
				typeName = L"[error]";
				break;
			case Messtype::warning:
				typeName = L"[warning]";
				break;
			case Messtype::information:
				typeName = L"[information]";
				break;
			case Messtype::informationNoPromp:
				typeName = L"[info]";
				break;
			}
			__logs.push_back(typeName + L": " + message);
		}
		if (haveConsole)
		{
			if (type == Messtype::showOnly)
			{
				std::wcout << assistanceName << ": " << message << std::endl;
			}
			else if (type == Messtype::error)
			{
				HANDLE outHwnd = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(outHwnd, 12 | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				std::wcout << assistanceName << ": " << message << std::endl;
				SetConsoleTextAttribute(outHwnd, 15);
			}
			else if (type == Messtype::information || type == Messtype::informationNoPromp)
			{
				HANDLE outHwnd = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(outHwnd, 11);
				std::wcout << assistanceName << ": " << message << std::endl;
				SetConsoleTextAttribute(outHwnd, 15);
			}
			else
			{
				HANDLE outHwnd = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(outHwnd, 14);
				std::wcout << assistanceName << ": " << message << std::endl;
				SetConsoleTextAttribute(outHwnd, 15);
			}
		}
		if (type != Messtype::showOnly && type != Messtype::informationNoPromp)
		{
			MessageBeep(static_cast<UINT>(type));
			MessageBox(__window_hwnd, message.c_str(), assistanceName.c_str(), static_cast<UINT>(type));
		}
		return returnValue;
	}

	void CommonTools::createConsole()
	{
		if (haveConsole) return;
		AllocConsole();
		freopen("CONIN$", "r+t", stdin);
		freopen("CONIN$", "w+t", stdout);
		_setmode(_fileno(stdout), _O_U16TEXT);  //This code is for Windows only, set console output to UTF-16
		_setmode(_fileno(stdin), _O_U16TEXT);    //This code is for Windows only, set console input to UTF-16
		haveConsole = true;
	}

	void CommonTools::freeConsole()
	{
		if (!haveConsole) return;
		FreeConsole();
		haveConsole = false;
	}

	CommonTools::CommonTools()
	{
		if (haveConsole)
		{
			_setmode(_fileno(stdout), _O_U16TEXT);  //This code is for Windows only, set console output to UTF-16
			_setmode(_fileno(stdin), _O_U16TEXT);    //This code is for Windows only, set console input to UTF-16
		}
		assistanceName = Base::getInstance().getTitle();
	}


	CommonTools::~CommonTools()
	{
	}
}