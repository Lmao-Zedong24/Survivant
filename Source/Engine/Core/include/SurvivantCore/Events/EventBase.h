//EventBase.h
#pragma once

namespace Core
{
	class EventBase
	{
	public:

	public:
		EventBase() = default;
		~EventBase() = default;

	public:
		virtual void ClearListeners() = 0;
	};
}