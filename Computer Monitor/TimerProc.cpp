#include "TimerProc.h"

namespace CM
{
	VOID CALLBACK TimerProc (HWND hwnd, UINT msg, UINT_PTR id, DWORD time)
	{
		CM::HWUDS *userdata = reinterpret_cast<CM::HWUDS *>(GetWindowLongPtr (hwnd, GWLP_USERDATA));

		if (id == userdata->SHOWTIMERID)
		{
			if (userdata->seconds_left == 0) //end of resting, wait for click
			{
				KillTimer (hwnd, userdata->SHOWTIMERID);
				CM::Utility::WriteText (hwnd, "Click to resume working...");
				userdata->waiting = true;
			}
			else //decrement counter and update screen
			{
				SetTimer (hwnd, userdata->SHOWTIMERID, 1000, TimerProc);
				CM::Utility::WriteText (hwnd, "Rest your eyes for " + CM::Utility::IntToString (userdata->seconds_left--) + " seconds...");
			}
		}
		else if (id == userdata->HIDETIMERID) //start rest counter
		{
			KillTimer (hwnd, userdata->HIDETIMERID);
			userdata->seconds_left = userdata->SHOWTIMEMS / 1000;

			//reprint window and activate
			CM::Utility::WriteText (hwnd, "Rest your eyes for " + CM::Utility::IntToString (userdata->seconds_left--) + "seconds...");
			SetWindowPos (hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			SetForegroundWindow (hwnd);
			ShowWindow (hwnd, SW_SHOW);
			SetTimer (hwnd, userdata->SHOWTIMERID, 1000, TimerProc);
		}
	}
}