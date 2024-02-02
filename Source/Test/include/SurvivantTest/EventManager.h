//EventManager.h

#pragma once
#include "IEvent.h"
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

		template <class T, typename ...Args>
		void Invoke(Args... p_paramaters);

		template <class T>
		T* AddEvent(std::shared_ptr<EventBase> p_event);

	public:
		EventManager() = default;
		~EventManager() = default;



	private:
		EventMap m_events;
	};

	template<class T, typename ...Args>
	void EventManager::Invoke(Args...p_paramaters)
	{
		if constexpr (!std::is_base_of_v<Event<Args...>, T> || !std::is_same_v<Event<Args...>, T>)
			return;

		EventId id = typeid(T).hash_code();

		if (m_events.contains(id))
			dynamic_cast<T*>(m_events[id].get())->Invoke(p_paramaters...);

	}
	template<class T>
	T* EventManager::AddEvent(std::shared_ptr<EventBase> p_event)
	{
		if constexpr (!(std::is_same_v<EventBase, T> || std::is_base_of_v<EventBase, T>))
			return nullptr;

		EventId id = typeid(T).hash_code();

		m_events.try_emplace(id, std::make_shared<T>());

		T* eventPtr = dynamic_cast<T*>(m_events[id].get());
		eventPtr->Combine<T>(*dynamic_cast<T*>(p_event.get()));

		return eventPtr;
	}
}


