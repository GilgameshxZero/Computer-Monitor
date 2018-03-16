#include "WinMain.h"

int WINAPI WinMain (HINSTANCE instance, HINSTANCE prev_inst, LPSTR cmd_line, int cmd_show)
{
	CM::HWUDS userdata;
	HWND host_wnd;
	MSG msg;
	WNDCLASSEX wcex;

	{//set constants and globals, read from config.ini
		std::ifstream config ("config.ini", std::ios::binary);
		config >> userdata.HIDETIMEMS >> userdata.SHOWTIMEMS;
		config.close ();

		userdata.CLASSNAME = "Computer Monitor - Rain Corporation";
		userdata.TITLETEXT = userdata.CLASSNAME;
		userdata.waiting = false;
		userdata.sleeping = false;
		userdata.SHOWTIMERID = 0;
		userdata.HIDETIMERID = 1;
		userdata.seconds_left = userdata.SHOWTIMEMS / 1000;
	}

	{//register and create host window
		wcex.cbSize			= sizeof (WNDCLASSEX);
		wcex.style			= NULL;
		wcex.lpfnWndProc	= CM::HostWndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= instance;
		wcex.hIcon			= static_cast<HICON>(LoadImage (instance, MAKEINTRESOURCE (IDI_COMPUTERMONITORICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));
		wcex.hCursor		= LoadCursor (NULL, IDC_ARROW);
		wcex.hbrBackground	= NULL;
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= userdata.CLASSNAME.c_str ();
		wcex.hIconSm		= static_cast<HICON>(LoadImage (instance, MAKEINTRESOURCE (IDI_COMPUTERMONITORICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE));

		if (!RegisterClassEx (&wcex))
		{
			MessageBox (NULL, ("The host window could not be registered. Error code: " + CM::Utility::IntToString (static_cast<int>(GetLastError ())) + ". Press OK to terminate program.").c_str (), "Error!", MB_OK);
			return -1;
		}

		host_wnd = CreateWindowEx (WS_EX_TOPMOST, userdata.CLASSNAME.c_str (), userdata.TITLETEXT.c_str (), WS_POPUP, 0, 0, GetSystemMetrics (SM_CXSCREEN), GetSystemMetrics (SM_CYSCREEN), NULL, NULL, instance, NULL);

		if (host_wnd == NULL)
		{
			MessageBox (NULL, ("The host window could not be created. Error code: " + CM::Utility::IntToString (static_cast<int>(GetLastError ())) + ". Press OK to terminate program.").c_str (), "Error!", MB_OK);
			return -1;
		}
	}

	{//window init
		SetWindowLongPtr (host_wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&userdata));

		ShowWindow (host_wnd, cmd_show);
		UpdateWindow (host_wnd);
		ShowWindow (host_wnd, SW_HIDE);

		SetTimer (host_wnd, userdata.HIDETIMERID, userdata.HIDETIMEMS, CM::TimerProc);
	}

	//message loop
	while(GetMessage (&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return static_cast<int>(msg.wParam);
}