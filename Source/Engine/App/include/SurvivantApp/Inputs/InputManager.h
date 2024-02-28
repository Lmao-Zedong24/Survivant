//InputManager.h

#pragma once
#include "KeyboardInputs.h"
#include "MouseInputs.h"
#include "InputType.h"

#include "SurvivantCore/Events/Event.h"
#include "SurvivantCore/Events/EventManager.h"

#include <memory>
#include <tuple>
#include <string>


namespace App
{
	//foward declaration
	class Window;

	class InputManager
	{
	public:
		//events
		using WindowCloseEvent = Core::Event<>;

		using KeyboardKeyType = InputType<EKey, EKeyState, EInputModifier>;
		using KeyCallbackParam = char;
		using KeyCallback = std::function<void(KeyCallbackParam)>;
		using MouseKeyType = InputType<EMouseButton, EMouseButtonState, EInputModifier>;
		using MouseCallback = std::function<void(float, float)>;

		InputManager() {}
		InputManager(InputManager const&) = delete;
		void operator=(InputManager const&) = delete;

		static InputManager& GetInstance();
		static std::string KeyBindingToString(const KeyboardKeyType& p_key);
		static std::string KeyNameToString(const EKey& p_name);
		static std::string KeyModifToString(const EInputModifier& p_modif);
		static EKey GetModifKey(const EInputModifier& p_modif);


		void InitWindow(Window* p_window);

		void CallInput(const KeyboardKeyType& p_type, char p_scancode);

		void AddInputBinding(const KeyboardKeyType& p_type, const KeyCallback& p_callback);

		template<class Event, typename ...Args>
		void AddInputEventBinding(const KeyboardKeyType& p_type, std::tuple<Args...> (*p_translate)(KeyCallbackParam));

		void CallInput(const MouseKeyType& p_type, float p_x, float p_y);

		void CallInput(const MouseKeyType& p_type);

		void AddInputBinding(const MouseKeyType& p_type, const MouseCallback& p_callback);

		template<class Event, typename ...Args>
		void AddInputEventBinding(const MouseKeyType& p_type, std::tuple<Args...>(*p_translate)(float, float));

		void GetMousePos(double& p_x, double& p_y);

		bool EvaluateInput(const KeyboardKeyType& p_key);
		bool EvaluateInput(const MouseKeyType& p_key);


	public:
		//container peripherique
		std::unordered_map<KeyboardKeyType, KeyCallback> m_keyCallbacks;
		std::unordered_map<MouseKeyType, MouseCallback> m_mouseKeyCallbacks;

		App::Window* m_glfwWindow = nullptr;

	};

	template<class T, typename ...Args>
	void InputManager::AddInputEventBinding(const KeyboardKeyType& p_type, std::tuple<Args...>(*p_translate)(KeyCallbackParam))
	{
		if constexpr (!std::is_base_of_v<Core::Event<Args...>, T> && !std::is_same_v<Core::Event<Args...>, T>)
			return;

		//needs to capture a copy of translate ptr
		KeyCallback callback = 
			[p_translate](KeyCallbackParam p_1)
			{ 
				Core::EventManager::GetInstance().Invoke<T>(p_translate(p_1));
			};

		m_keyCallbacks.emplace(p_type, callback);

	}

	template<class T, typename ...Args>
	inline void InputManager::AddInputEventBinding(const MouseKeyType& p_type, std::tuple<Args...>(*p_translate)(float, float))
	{
		if constexpr (!std::is_base_of_v<Core::Event<Args...>, T> && !std::is_same_v<Core::Event<Args...>, T>)
			return;

		//needs to capture a copy of translate ptr
		MouseCallback callback =
			[p_translate](float p_1, float p_2)
			{
				Core::EventManager::GetInstance().Invoke<T>(p_translate(p_1, p_2));
			};

		m_mouseKeyCallbacks.emplace(p_type, callback);
	}

	//glfwSetKeyCallback(window, key_callback);

	//GLFW input callbacks

	//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	//{
	//	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	//		activate_airship();
	//}

}


