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
	case EKey::UNKNOWN:			return "UNKNOWN";
	case EKey::SPACE:			return "SPACE";
	case EKey::APOSTROPHE:
	case EKey::COMMA:
	case EKey::MINUS:
	case EKey::PERIOD:
	case EKey::SLASH:
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
	case EKey::SEMICOLON:
	case EKey::EQUAL:
	case EKey::A:
	case EKey::B:
	case EKey::C:
	case EKey::D:
	case EKey::E:
	case EKey::F:
	case EKey::G:
	case EKey::H:
	case EKey::I:
	case EKey::J:
	case EKey::K:
	case EKey::L:
	case EKey::M:
	case EKey::N:
	case EKey::O:
	case EKey::P:
	case EKey::Q:
	case EKey::R:
	case EKey::S:
	case EKey::T:
	case EKey::U:
	case EKey::V:
	case EKey::W:
	case EKey::X:
	case EKey::Y:
	case EKey::Z:
	case EKey::LEFT_BRACKET:
	case EKey::BACKSLASH:
	case EKey::RIGHT_BRACKET:
	case EKey::GRAVE_ACCENT:	return std::string(1, static_cast<char>(p_name));
	case EKey::WORLD_1:			return "WORLD_1";
	case EKey::WORLD_2:			return "WORLD_2";
	case EKey::ESCAPE:			return "ESCAPE";
	case EKey::ENTER:			return "ENTER";
	case EKey::TAB:				return "TAB";
	case EKey::BACKSPACE:		return "BACKSPACE";
	case EKey::INSERT:			return "INSERT";
	case EKey::DEL:				return "DELETE";
	case EKey::RIGHT:			return "RIGHT";
	case EKey::LEFT:			return "LEFT";
	case EKey::DOWN:			return "DOWN";
	case EKey::UP:				return "UP";
	case EKey::PAGE_UP:			return "PAGE_UP";
	case EKey::PAGE_DOWN:		return "PAGE_DOWN";
	case EKey::HOME:			return "HOME";
	case EKey::END:				return "END";
	case EKey::CAPS_LOCK:		return "CAPS_LOCK";
	case EKey::SCROLL_LOCK:		return "SCROLL_LOCK";
	case EKey::NUM_LOCK:		return "NUM_LOCK";
	case EKey::PRINT_SCREEN:	return "PRINT_SCREEN";
	case EKey::PAUSE:			return "PAUSE"; 
	case EKey::F1 :
	case EKey::F2 :
	case EKey::F3 :
	case EKey::F4 :
	case EKey::F5 :
	case EKey::F6 :
	case EKey::F7 :
	case EKey::F8 :
	case EKey::F9 :
	case EKey::F10:
	case EKey::F11:
	case EKey::F12:
	case EKey::F13:
	case EKey::F14:
	case EKey::F15:
	case EKey::F16:
	case EKey::F17:
	case EKey::F18:
	case EKey::F19:
	case EKey::F20:
	case EKey::F21:
	case EKey::F22:
	case EKey::F23:
	case EKey::F24:
	case EKey::F25:				return "F" + std::to_string((static_cast<int>(p_name) % 290) + 1);
	case EKey::KP_0:
	case EKey::KP_1:
	case EKey::KP_2:
	case EKey::KP_3:
	case EKey::KP_4:
	case EKey::KP_5:
	case EKey::KP_6:
	case EKey::KP_7:
	case EKey::KP_8:
	case EKey::KP_9:			return "KP_" + std::to_string((static_cast<int>(p_name) % 320) + 1);
	case EKey::KP_DECIMAL:		return "KP_DECIMAL";
	case EKey::KP_DIVIDE:		return "KP_DIVIDE";
	case EKey::KP_MULTIPLY:		return "KP_SUBTRACT";
	case EKey::KP_SUBTRACT:		return "KP_SUBTRACT";
	case EKey::KP_ADD:			return "KP_ADD";
	case EKey::KP_ENTER:		return "KP_ENTER";
	case EKey::KP_EQUAL:		return "KP_EQUAL";
	case EKey::LEFT_SHIFT:		return "LEFT_SHIFT";
	case EKey::LEFT_CONTROL:	return "LEFT_CONTROL";
	case EKey::LEFT_ALT:		return "LEFT_ALT";
	case EKey::LEFT_SUPER:		return "LEFT_SUPER";
	case EKey::RIGHT_SHIFT:		return "RIGHT_SHIFT";
	case EKey::RIGHT_CONTROL:	return "RIGHT_CONTROL";
	case EKey::RIGHT_ALT:		return "RIGHT_ALT";
	case EKey::RIGHT_SUPER:		return "RIGHT_SUPER";
	case EKey::MENU:			return "MENU";

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
		return EKey::LEFT_SHIFT;
	case App::EInputModifier::MOD_CONTROL:
		return EKey::LEFT_CONTROL;
	case App::EInputModifier::MOD_ALT:
		return EKey::LEFT_ALT;
	case App::EInputModifier::MOD_SUPER:
		return EKey::LEFT_SUPER;
	case App::EInputModifier::MOD_CAPS_LOCK:
		return EKey::CAPS_LOCK;
	case App::EInputModifier::MOD_NUM_LOCK:
		return EKey::NUM_LOCK;
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

