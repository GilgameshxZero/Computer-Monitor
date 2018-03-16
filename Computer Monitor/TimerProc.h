#pragma once
#include <Windows.h>
#include "HWUDS.h"
#include "Utility.h"

namespace CM
{
	VOID CALLBACK TimerProc (HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
}