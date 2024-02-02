//EventManager.h

#pragma once
#include "IEvent.h"
#include "Event.h"

#include <map>
#include <vector>
#include <memory>
#include <type_traits>

namespace Core
{
	class EventManager
	{
	private:
		using EventId = size_t;
		using EventMap = std::map<EventId, std::shared_ptr<EventBase>>;

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
	inline void EventManager::Invoke(Args...p_paramaters)
	{
		//if (!std::is_base_of<Event<Args...>, T>::value || !std::is_same<Event<Args...>, T>::value)
		//	return;

		EventId id = typeid(T).hash_code();

		if (m_events.contains(id))
			dynamic_cast<T*>(m_events[id].get())->Invoke(p_paramaters...);

	}
	template<class T>
	inline T* EventManager::AddEvent(std::shared_ptr<EventBase> p_event)
	{
		if constexpr (!(std::is_same_v<EventBase, T> || std::is_base_of_v<EventBase, T>))
			return nullptr;

		EventId id = typeid(T).hash_code();

		if (!m_events.contains(id))
			m_events[id] = p_event != nullptr? p_event: std::make_shared<T>();
		else
		{
			(dynamic_cast<T*>(m_events[id].get()))->Combine<T>(*dynamic_cast<T*>(p_event.get()));
		}
		
		return nullptr;
	}
}


