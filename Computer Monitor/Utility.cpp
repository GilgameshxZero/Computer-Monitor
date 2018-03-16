#include "Utility.h"

namespace CM
{
	namespace Utility
	{
		std::string IntToString (int number)
		{
			std::ostringstream outstream;

			outstream << number;
			return outstream.str ();
		}
		int StringToInt (std::string string)
		{
			std::istringstream instream (string);
			int number;

			instream >> number;
			return number;
		}

		int WriteText (HWND hwnd, std::string screen_text, int font_size)
		{
			HBRUSH bk_brush, original_brush;
			HDC hdc = GetDC (hwnd);
			HFONT text_font, original_font;
			RECT crect;
			SIZE text_size;

			//First, set the DC to the font of the words to print.
			text_font = CreateFont (-MulDiv (font_size, GetDeviceCaps (hdc, LOGPIXELSY), 72), 0, 0, 0, 0, false, false, false, 0, 0, 0, 0, 0, "Verdana");

			//If font creation failed, return immediately and exit program.
			if (!text_font)
			{
				MessageBox (NULL, "Font creation failed!", "Error", MB_OK);
				PostQuitMessage (-1);

				return -1;
			}

			//Select font
			original_font = reinterpret_cast<HFONT>(SelectObject (hdc, text_font));

			//Set up the background brush to black, and use the DC to select it.
			bk_brush = CreateSolidBrush (RGB (0,0,0));
			original_brush = reinterpret_cast<HBRUSH>(SelectObject (hdc, bk_brush));

			//Set the text color to white and the text background to black.
			SetTextColor (hdc, RGB (255,255,255));
			SetBkColor (hdc, RGB (0,0,0));

			//Draw the words on the screen, centered, and paint the background.
			GetClientRect (hwnd, &crect);
			Rectangle (hdc, crect.left, crect.top, crect.right, crect.bottom);
			GetTextExtentPoint32 (hdc, screen_text.c_str (), static_cast<int>(screen_text.length ()), &text_size);
			TextOut (hdc, crect.right / 2 - text_size.cx / 2, crect.bottom / 2 - text_size.cy / 2, screen_text.c_str (), static_cast<int>(screen_text.length ()));

			//Free up the DCs and objects.
			SelectObject (hdc, original_font);
			SelectObject (hdc, original_brush);
			DeleteObject (text_font);
			DeleteObject (bk_brush);
			ReleaseDC (hwnd, hdc);

			return 0;
		}
	}
}