//IMenuable.h
#pragma once

#include "IPanelable.h"

namespace UI
{
	class IMenuable
	{
	public:
		virtual ~IMenuable() = default;
		virtual void DisplayAndUpdateMenu() = 0;
	};	
}
