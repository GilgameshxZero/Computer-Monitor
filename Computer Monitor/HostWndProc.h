#pragma once
#include <string>
#include <Windows.h>
#include "HWUDS.h"
#include "TimerProc.h"
#include "Utility.h"

namespace CM
{
	LRESULT CALLBACK HostWndProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
}