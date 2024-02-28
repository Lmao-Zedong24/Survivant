//IPanelable.h
#pragma once

namespace UI
{
	class IPanelable
	{
	public:
		virtual ~IPanelable() = default;
		virtual void DisplayAndUpdatePanel() = 0;
	};
}
