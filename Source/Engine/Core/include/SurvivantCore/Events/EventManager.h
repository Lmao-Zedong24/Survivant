//EventManager.h
#pragma once

#include "EventBase.h"
#include "Event.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include <type_traits>

namespace Core
{
	class EventManager
	{
	private:
		using EventId = size_t;
		using EventMap = std::unordered_map<EventId, std::shared_ptr<EventBase>>;

	public:
		EventManager() {}
		EventManager(EventManager const&) = delete;
		void operator=(EventManager const&) = delete;

	public:
		static EventManager& GetInstance();

	public:
		template <class T, typename ...Args>
		void Invoke(Args... p_paramaters);

		template <class T, typename ...Args>
		void Invoke(const std::tuple<Args...>& p_paramaters);
		
		//cant add event bcs of listener ids
		//template <class T>
		//T* AddEvent(EventBase* p_event);

		template <class T, class U = T::EventDelegate>
		EventId AddListenner(const U& p_callback);

		template <class T>
		bool RemoveListenner(const Event<>::ListenerId& p_callback);

	private:
		template <class T>
		friend EventId GetEventId();

	private:
		EventMap m_events;
	};

	template<class T, typename ...Args>
	void EventManager::Invoke(Args...p_paramaters)
	{
		static_assert((std::is_base_of_v<Event<Args...>, T> || std::is_same_v<Event<Args...>, T>),
			"Event can not be Invoked, parameters are invalid");

		EventId id = GetEventId<T>();

		if (m_events.contains(id))
			dynamic_cast<T*>(m_events[id].get())->Invoke(p_paramaters...);

	}

	template<class T, typename ...Args>
	inline void EventManager::Invoke(const std::tuple<Args...>& p_paramaters)
	{
		if constexpr (!std::is_base_of_v<Event<Args...>, T> && !std::is_same_v<Event<Args...>, T>)
			return;

		std::apply([this](auto &&... args) { this->Invoke<T>(args...); }, p_paramaters);
	}

	template <class T, class U>
	inline Event<>::ListenerId EventManager::AddListenner(const U& p_callback)
	{
		if constexpr (!std::is_same_v<EventBase, T> && !std::is_base_of_v<EventBase, T>)
			return nullptr;

		EventId id = GetEventId<T>();

		m_events.try_emplace(id, std::make_shared<T>());

		T* eventPtr = dynamic_cast<T*>(m_events[id].get());
		return eventPtr->AddListener(p_callback);
	}

	template<class T>
	inline bool EventManager::RemoveListenner(const Event<>::ListenerId& p_id)
	{
		if constexpr (!std::is_same_v<EventBase, T> && !std::is_base_of_v<EventBase, T>)
			return false;

		EventId id = GetEventId<T>();
		auto event = m_events.find(id);

		if (event == m_events.end())
			return false;

		dynamic_cast<T*>(event->second.get())->RemoveListener(p_id);
		return true;
	}

	template<class T>
	EventManager::EventId GetEventId()
	{
		return typeid(T).hash_code();
	}
}


