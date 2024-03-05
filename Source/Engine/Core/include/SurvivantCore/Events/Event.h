//Event.h
#pragma once

#include "EventBase.h"

#include <set>
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
		using ListenerId = size_t;

	public:
		Event() = default;
		~Event() = default;

		void						ClearListeners() override;

		ListenerId					AddListener(const EventDelegate& p_delegate);
		std::vector<ListenerId>		AddListeners(const std::vector<EventDelegate>& p_delegates);
		void						RemoveListener(const ListenerId& p_id);
		void						RemoveListeners(const std::vector<ListenerId>& p_id);
		void						Invoke(Args... p_parameters);
		
		virtual void	BeforeInvoke() {};
		virtual void	AfterInvoke() {};

		//cant combine bcs of Listener ids
		//template<class T>
		//void Combine(const T& p_other);

	private:
		std::unordered_map<size_t, EventDelegate>	m_listeners;
		ListenerId									m_nextId = 0;
	};

	template<typename ...Args>
	inline void Event<Args...>::ClearListeners()
	{
		m_listeners.clear();
	}

	template<typename ...Args>
	inline Event<Args...>::ListenerId Event<Args...>::AddListener(const EventDelegate& p_delegate)
	{
		m_listeners.emplace(m_nextId, p_delegate);
		return m_nextId++;
	}

	template<typename ...Args>
	inline std::vector<Event<>::ListenerId> Event<Args...>::AddListeners(const std::vector<EventDelegate>& p_delegates)
	{
		std::vector<ListenerId> ids(p_delegates.size());

		for (auto& delegate : p_delegates)
			ids.push_back(AddListener(delegate));

		return ids;
	}



	template<typename ...Args>
	inline void Event<Args...>::RemoveListener(const ListenerId& p_id)
	{
		m_listeners.erase(p_id);
	}

	template<typename ...Args>
	inline void Event<Args...>::RemoveListeners(const std::vector<ListenerId>& p_ids)
	{
		m_listeners.erase(p_ids);
	}

	template<typename ...Args>
	void Event<Args...>::Invoke(Args... p_parameters)
	{
		BeforeInvoke();

		for (auto& pair : m_listeners)
		{
			auto& eventDelegate = pair.second;
			eventDelegate(p_parameters...);
		}

		AfterInvoke();
	}

	//template<typename ...Args>
	//template<class T>
	//inline void Event<Args...>::Combine(const T& p_other)
	//{
	//	this->AddListeners(p_other.m_listeners);
	//}
}