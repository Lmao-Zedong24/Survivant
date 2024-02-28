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

		template <class T>
		T* AddEvent(EventBase* p_event);

		template <class T, class U = T::EventDelegate>
		T* AddListenner(const U& p_callback);

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

	template<class T>
	T* EventManager::AddEvent(EventBase* p_event)
	{
		if constexpr (!std::is_same_v<EventBase, T> && !std::is_base_of_v<EventBase, T>)
			return nullptr;

		EventId id = GetEventId<T>();

		m_events.try_emplace(id, std::make_shared<T>());

		T* eventPtr = dynamic_cast<T*>(m_events[id].get());
		eventPtr->Combine<T>(*dynamic_cast<T*>(p_event));

		return eventPtr;
	}

	template <class T, class U>
	inline T* EventManager::AddListenner(const U& p_callback)
	{
		if constexpr (!std::is_same_v<EventBase, T> && !std::is_base_of_v<EventBase, T>)
			return nullptr;

		//auto tmp = std::make_shared<T>();

		EventId id = GetEventId<T>();

		m_events.try_emplace(id, std::make_shared<T>());

		T* eventPtr = dynamic_cast<T*>(m_events[id].get());
		eventPtr->AddListener(p_callback);

		return eventPtr;
	}

	template<class T>
	EventManager::EventId GetEventId()
	{
		return typeid(T).hash_code();
	}
}


