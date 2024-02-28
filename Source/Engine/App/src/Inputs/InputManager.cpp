//InputManager.cpp

#include "SurvivantApp/Inputs/InputManager.h"
#include "SurvivantApp/Windows/Window.h"

#include <tuple>

using namespace App;

InputManager& App::InputManager::GetInstance()
{
	static InputManager s_instance;

	return s_instance;
}

std::string App::InputManager::KeyBindingToString(const KeyboardKeyType& p_key)
{
	std::string str;
	auto& infoRef = p_key.m_inputInfo;
	EInputModifier keyModif = std::get<2>(infoRef);
	
	for (size_t i = 0; i < NUM_INPUT_MODIFIERS; i++)
	{
		auto modif = EInputModifier(1 << i);
		if (keyModif & modif)
			str += (KeyModifToString(modif) + '+');
	}
	str += KeyNameToString(std::get<0>(infoRef));

	return str;
}

std::string App::InputManager::KeyNameToString(const EKey& p_name)
{
	switch (p_name)
	{
	case EKey::KEY_UNKNOWN:			return "UNKNOWN";
	case EKey::KEY_SPACE:			return "SPACE";
	case EKey::KEY_APOSTROPHE:
	case EKey::KEY_COMMA:
	case EKey::KEY_MINUS:
	case EKey::KEY_PERIOD:
	case EKey::KEY_SLASH:
	case EKey::KEY_0:
	case EKey::KEY_1:
	case EKey::KEY_2:
	case EKey::KEY_3:
	case EKey::KEY_4:
	case EKey::KEY_5:
	case EKey::KEY_6:
	case EKey::KEY_7:
	case EKey::KEY_8:
	case EKey::KEY_9:
	case EKey::KEY_SEMICOLON:
	case EKey::KEY_EQUAL:
	case EKey::KEY_A:
	case EKey::KEY_B:
	case EKey::KEY_C:
	case EKey::KEY_D:
	case EKey::KEY_E:
	case EKey::KEY_F:
	case EKey::KEY_G:
	case EKey::KEY_H:
	case EKey::KEY_I:
	case EKey::KEY_J:
	case EKey::KEY_K:
	case EKey::KEY_L:
	case EKey::KEY_M:
	case EKey::KEY_N:
	case EKey::KEY_O:
	case EKey::KEY_P:
	case EKey::KEY_Q:
	case EKey::KEY_R:
	case EKey::KEY_S:
	case EKey::KEY_T:
	case EKey::KEY_U:
	case EKey::KEY_V:
	case EKey::KEY_W:
	case EKey::KEY_X:
	case EKey::KEY_Y:
	case EKey::KEY_Z:
	case EKey::KEY_LEFT_BRACKET:
	case EKey::KEY_BACKSLASH:
	case EKey::KEY_RIGHT_BRACKET:
	case EKey::KEY_GRAVE_ACCENT:	return std::string(1, static_cast<char>(p_name));
	case EKey::KEY_WORLD_1:			return "WORLD_1";
	case EKey::KEY_WORLD_2:			return "WORLD_2";
	case EKey::KEY_ESCAPE:			return "ESCAPE";
	case EKey::KEY_ENTER:			return "ENTER";
	case EKey::KEY_TAB:				return "TAB";
	case EKey::KEY_BACKSPACE:		return "BACKSPACE";
	case EKey::KEY_INSERT:			return "INSERT";
	case EKey::KEY_DELETE:			return "DELETE";
	case EKey::KEY_RIGHT:			return "RIGHT";
	case EKey::KEY_LEFT:			return "LEFT";
	case EKey::KEY_DOWN:			return "DOWN";
	case EKey::KEY_UP:				return "UP";
	case EKey::KEY_PAGE_UP:			return "PAGE_UP";
	case EKey::KEY_PAGE_DOWN:		return "PAGE_DOWN";
	case EKey::KEY_HOME:			return "HOME";
	case EKey::KEY_END:				return "END";
	case EKey::KEY_CAPS_LOCK:		return "CAPS_LOCK";
	case EKey::KEY_SCROLL_LOCK:		return "SCROLL_LOCK";
	case EKey::KEY_NUM_LOCK:		return "NUM_LOCK";
	case EKey::KEY_PRINT_SCREEN:	return "PRINT_SCREEN";
	case EKey::KEY_PAUSE:			return "PAUSE"; 
	case EKey::KEY_F1 :
	case EKey::KEY_F2 :
	case EKey::KEY_F3 :
	case EKey::KEY_F4 :
	case EKey::KEY_F5 :
	case EKey::KEY_F6 :
	case EKey::KEY_F7 :
	case EKey::KEY_F8 :
	case EKey::KEY_F9 :
	case EKey::KEY_F10:
	case EKey::KEY_F11:
	case EKey::KEY_F12:
	case EKey::KEY_F13:
	case EKey::KEY_F14:
	case EKey::KEY_F15:
	case EKey::KEY_F16:
	case EKey::KEY_F17:
	case EKey::KEY_F18:
	case EKey::KEY_F19:
	case EKey::KEY_F20:
	case EKey::KEY_F21:
	case EKey::KEY_F22:
	case EKey::KEY_F23:
	case EKey::KEY_F24:
	case EKey::KEY_F25:				return "F" + std::to_string((static_cast<int>(p_name) % 290) + 1);
	case EKey::KEY_KP_0:
	case EKey::KEY_KP_1:
	case EKey::KEY_KP_2:
	case EKey::KEY_KP_3:
	case EKey::KEY_KP_4:
	case EKey::KEY_KP_5:
	case EKey::KEY_KP_6:
	case EKey::KEY_KP_7:
	case EKey::KEY_KP_8:
	case EKey::KEY_KP_9:			return "KP_" + std::to_string((static_cast<int>(p_name) % 320) + 1);
	case EKey::KEY_KP_DECIMAL:		return "KP_DECIMAL";
	case EKey::KEY_KP_DIVIDE:		return "KP_DIVIDE";
	case EKey::KEY_KP_MULTIPLY:		return "KP_SUBTRACT";
	case EKey::KEY_KP_SUBTRACT:		return "KP_SUBTRACT";
	case EKey::KEY_KP_ADD:			return "KP_ADD";
	case EKey::KEY_KP_ENTER:		return "KP_ENTER";
	case EKey::KEY_KP_EQUAL:		return "KP_EQUAL";
	case EKey::KEY_LEFT_SHIFT:		return "LEFT_SHIFT";
	case EKey::KEY_LEFT_CONTROL:	return "LEFT_CONTROL";
	case EKey::KEY_LEFT_ALT:		return "LEFT_ALT";
	case EKey::KEY_LEFT_SUPER:		return "LEFT_SUPER";
	case EKey::KEY_RIGHT_SHIFT:		return "RIGHT_SHIFT";
	case EKey::KEY_RIGHT_CONTROL:	return "RIGHT_CONTROL";
	case EKey::KEY_RIGHT_ALT:		return "RIGHT_ALT";
	case EKey::KEY_RIGHT_SUPER:		return "RIGHT_SUPER";
	case EKey::KEY_MENU:			return "MENU";

	default:						return "";
	}
}

std::string App::InputManager::KeyModifToString(const EInputModifier& p_modif)
{
	switch (p_modif)
	{
	case App::EInputModifier::MOD_SHIFT:		return "SHIFT";
	case App::EInputModifier::MOD_CONTROL:		return "CONTROL";
	case App::EInputModifier::MOD_ALT:			return "ALT";
	case App::EInputModifier::MOD_SUPER:		return "SUPER";
	case App::EInputModifier::MOD_CAPS_LOCK:	return "CAPS_LOCK";
	case App::EInputModifier::MOD_NUM_LOCK:		return "NUM_LOCK";

	default:									return std::string();
	}
}

EKey App::InputManager::GetModifKey(const EInputModifier& p_modif)
{
	//gotat put this if I want to use enum. guess not
//#undef MOD_SHIFT
//#undef MOD_CONTROL
//#undef MOD_ALT
	switch (p_modif)
	{
	case App::EInputModifier::MOD_SHIFT:
		return EKey::KEY_LEFT_SHIFT;
	case App::EInputModifier::MOD_CONTROL:
		return EKey::KEY_LEFT_CONTROL;
	case App::EInputModifier::MOD_ALT:
		return EKey::KEY_LEFT_ALT;
	case App::EInputModifier::MOD_SUPER:
		return EKey::KEY_LEFT_SUPER;
	case App::EInputModifier::MOD_CAPS_LOCK:
		return EKey::KEY_CAPS_LOCK;
	case App::EInputModifier::MOD_NUM_LOCK:
		return EKey::KEY_NUM_LOCK;
	default:
		return EKey();
	}
}

void App::InputManager::InitWindow(Window* p_window)
{
	if (p_window == nullptr)
		return;

	m_glfwWindow = p_window;
	m_glfwWindow->SetupInputManagerCallbacks();
	m_glfwWindow->SetupWindowCallbacks();
}

void App::InputManager::CallInput(const KeyboardKeyType& p_type, char p_scancode)
{
	auto callback = m_keyCallbacks.find(p_type);

	if (callback == m_keyCallbacks.end())
		return;

	//calls keyboard callback with scancode
	callback->second(p_scancode);
}

void App::InputManager::AddInputBinding(
	const KeyboardKeyType& p_type, 
	const KeyCallback& p_callback)
{
	m_keyCallbacks.emplace(p_type, p_callback);
}

void App::InputManager::CallInput(const MouseKeyType& p_type, float p_x, float p_y)
{
	auto callback = m_mouseKeyCallbacks.find(p_type);

	if (callback == m_mouseKeyCallbacks.end())
		return;

	//calls mouse key callback with mous pos (x,y)
	callback->second(p_x, p_y);
}

void App::InputManager::CallInput(const MouseKeyType& p_type)
{
	double i, j;
	GetMousePos(i, j);
	CallInput(p_type, static_cast<float>(i), static_cast<float>(j));
}

void App::InputManager::AddInputBinding(const MouseKeyType& p_type, const MouseCallback& p_callback)
{
	m_mouseKeyCallbacks.emplace(p_type, p_callback);
}

void App::InputManager::GetMousePos(double& p_x, double& p_y)
{
	m_glfwWindow->GetMousePos(p_x, p_y);
}

bool App::InputManager::EvaluateInput(const KeyboardKeyType& p_key)
{
	//std::apply(std::bind_front(&App::Window::EvaluateInput, m_glfwWindow), p_key.m_inputInfo);
	auto& info = p_key.m_inputInfo;
	return m_glfwWindow->EvaluateInput(std::get<0>(info), std::get<1>(info), std::get<2>(info));
}

bool App::InputManager::EvaluateInput(const MouseKeyType& p_key)
{
	auto& info = p_key.m_inputInfo;
	return m_glfwWindow->EvaluateInput(std::get<0>(info), std::get<1>(info), std::get<2>(info));
}

