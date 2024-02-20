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

void App::InputManager::InitWindow(Window* p_window)
{
	if (p_window == nullptr)
		return;

	m_window = p_window;
	m_window->SetupInputManager();
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
	m_window->GetMousePos(p_x, p_y);
}

bool App::InputManager::EvaluateInput(const KeyboardKeyType& p_key)
{
	//std::apply(std::bind_front(&App::Window::EvaluateInput, m_window), p_key.m_inputInfo);
	auto& info = p_key.m_inputInfo;
	return m_window->EvaluateInput(std::get<0>(info), std::get<1>(info), std::get<2>(info));
}

bool App::InputManager::EvaluateInput(const MouseKeyType& p_key)
{
	auto& info = p_key.m_inputInfo;
	return m_window->EvaluateInput(std::get<0>(info), std::get<1>(info), std::get<2>(info));
}

