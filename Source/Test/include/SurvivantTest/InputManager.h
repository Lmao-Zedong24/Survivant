//InputManager.h

#pragma once
#include "InputType.h"
#include "Event.h"
#include "EventManager.h"

#include <memory>
#include <tuple>

namespace App
{
	class InputManager
	{
	private:
		//friend class EventManager;

	public:
		using GLFWwindow = int;
		using KeyboardKeyType = InputType<int, int, int>;
		using KeyCallback = std::function<void(int)>;
		
		using MouseKeyType = InputType<GLFWwindow*>;
		using MouseCallback = std::function<void(float, float)>;

	public:
		InputManager() {}
		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

	public:
		static InputManager& GetInstance();

	public:
		void CallInput(const KeyboardKeyType& p_type);

		void AddInputBinding(const KeyboardKeyType& p_type, const KeyCallback& p_callback);

		template<class Event, typename ...Args>
		void AddInputEventBinding(const KeyboardKeyType& p_type, std::tuple<Args...> (*p_translate)(int));


		void CallInput(const MouseKeyType& p_type);

		void AddInputBinding(const MouseKeyType& p_type, const MouseCallback& p_callback);

		template<class Event, typename ...Args>
		void AddInputEventBinding(const MouseKeyType& p_type, std::tuple<Args...>(*p_translate)(float, float));

		//void AddInputBinding();
		//void AddInputBinding();

	public:
		//container peripherique
		std::unordered_map<KeyboardKeyType, KeyCallback> m_keyCallbacks;
		std::unordered_map<MouseKeyType, MouseCallback> m_mouseKeyCallbacks;


	};

	template<class T, typename ...Args>
	void InputManager::AddInputEventBinding(const KeyboardKeyType& p_type, std::tuple<Args...>(*p_translate)(int))
	{
		if constexpr (!std::is_base_of_v<Core::Event<Args...>, T> || !std::is_same_v<Core::Event<Args...>, T>)
			return;

		KeyCallback callback = 
			[&p_translate](int i)
			{ 
				Core::EventManager::GetInstance().Invoke<T>(p_translate(i));
			};

		m_keyCallbacks.emplace(p_type, callback);

	}

	template<class Event, typename ...Args>
	inline void InputManager::AddInputEventBinding(const MouseKeyType& p_type, std::tuple<Args...>(*p_translate)(float, float))
	{
	}

	//glfwSetKeyCallback(window, key_callback);

	//GLFW input callbacks

	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	//{
	//	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	//		activate_airship();
	//}

}


