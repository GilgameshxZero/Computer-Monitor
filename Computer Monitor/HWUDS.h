#pragma once
#include <string>
#include <Windows.h>

namespace CM
{
	class HWUDS
	{
		public:
			std::string	CLASSNAME;
			std::string	TITLETEXT;
			int			HIDETIMEMS; //work period
			int			SHOWTIMEMS; //rest period
			int			HIDETIMERID;
			int			SHOWTIMERID;
			int			seconds_left; //seconds left in rest period
			bool		waiting; //waiting for user click?
			bool		sleeping; //computer sleeping?
	};
}