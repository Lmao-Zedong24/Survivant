//IMenuable.h
#pragma once

namespace UI
{
	class IMenuable
	{
	public:
		virtual ~IMenuable() = default;
		virtual void DisplayAndUpdateMenu() = 0;
	};
}
