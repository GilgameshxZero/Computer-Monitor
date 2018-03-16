#include "HostWndProc.h"

namespace CM
{
	LRESULT CALLBACK HostWndProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		CM::HWUDS *userdata = reinterpret_cast<CM::HWUDS *>(GetWindowLongPtr (hwnd, GWLP_USERDATA));

		switch (msg)
		{
			case WM_LBUTTONDOWN:
			{
				if (userdata->waiting)
				{
					ShowWindow (hwnd, SW_HIDE);
					SetTimer (hwnd, userdata->HIDETIMERID, userdata->HIDETIMEMS, CM::TimerProc);
					KillTimer (hwnd, userdata->SHOWTIMERID);
					userdata->waiting = false;
				}

				break;
			}

			case WM_POWERBROADCAST:
			{
				if (wparam == PBT_APMSUSPEND)//sleeping, mark flag
					userdata->sleeping = true;
				else if (wparam == PBT_APMRESUMESUSPEND)//reset timer
				{
					if (userdata->sleeping)
					{
						userdata->sleeping = false;
						userdata->waiting = true;
						userdata->seconds_left = userdata->HIDETIMEMS / 1000;
						ShowWindow (hwnd, SW_HIDE);
						SetTimer (hwnd, userdata->HIDETIMERID, userdata->HIDETIMEMS, CM::TimerProc);
						KillTimer (hwnd, userdata->SHOWTIMERID);
					}
				}

				break;
			}

			case WM_CLOSE:
			{
				PostQuitMessage (1);
				break;
			}

			default:
				break;
		}

		return DefWindowProc (hwnd, msg, wparam, lparam);
	}
}