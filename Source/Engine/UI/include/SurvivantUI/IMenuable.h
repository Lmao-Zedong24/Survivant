//IMenuable.h
#pragma once

#include "IPanelable.h"

namespace UI
{
	class IMenuable
	{
	public:
		virtual ~IMenuable() = default;
		virtual IMenuable* Clone() const = 0;
		virtual void DisplayAndUpdateMenu() = 0;
	};	
}
