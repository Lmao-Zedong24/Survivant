//InputManager.cpp

#include "SurvivantTest/InputManager.h"

using namespace App;

InputManager& App::InputManager::GetInstance()
{
	static InputManager s_instance;

	return s_instance;
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

void App::InputManager::AddInputBinding(const MouseKeyType& p_type, const MouseCallback& p_callback)
{
	m_mouseKeyCallbacks.emplace(p_type, p_callback);
}
