//Event.h

#pragma once

#include "EventBase.h"

#include <functional>
#include <vector>
#include <memory>

namespace Core
{
	template <typename ...Args>
	class Event : public EventBase
	{
	public:
		typedef std::function<void(Args&...)> EventDelegate;

	public:
		Event() = default;
		~Event() = default;

	public:
		void ClearListeners() override;

	public:
		void AddListener(EventDelegate p_delegate);
		void AddListeners(std::vector<EventDelegate> p_delegates);
		void RemoveListener(EventDelegate p_delegate);
	
		void Invoke(Args... p_parameters);

	public:
		template<class T>
		void Combine(const T& p_other);

	private:
		std::vector<EventDelegate> m_listeners;
	};

	template<typename ...Args>
	inline void Event<Args...>::ClearListeners()
	{
		m_listeners.clear();
	}

	template<typename ...Args>
	inline void Event<Args...>::AddListener(EventDelegate p_delegate)
	{
		m_listeners.push_back(p_delegate);
	}

	template<typename ...Args>
	inline void Event<Args...>::AddListeners(std::vector<EventDelegate> p_delegates)
	{
		m_listeners.insert(m_listeners.end(), p_delegates.begin(), p_delegates.end());
	}

	template<typename ...Args>
	inline void Event<Args...>::RemoveListener(EventDelegate p_delegate)
	{
		m_listeners.push_back(p_delegate);
	}

	template<typename ...Args>
	void Event<Args...>::Invoke(Args... p_parameters)
	{
		for (EventDelegate& eventDelegate : m_listeners)
		{
			eventDelegate(p_parameters...);
		}
	}

	template<typename ...Args>
	template<class T>
	inline void Event<Args...>::Combine(const T& p_other)
	{
		this->AddListeners(p_other.m_listeners);
	}
}