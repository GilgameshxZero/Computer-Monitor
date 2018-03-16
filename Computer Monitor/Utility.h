#pragma once
#include <sstream>
#include <string>
#include <Windows.h>

namespace CM
{
	namespace Utility
	{
		std::string IntToString (int number);
		int StringToInt (std::string string);

		int WriteText (HWND hwnd, std::string screen_text, int font_size = 40);
	}
}