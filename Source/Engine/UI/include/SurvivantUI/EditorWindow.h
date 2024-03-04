//EditorWindow.h
#pragma once

#include "SurvivantApp/Windows/Window.h"
#include "SurvivantUI/UI.h"

#include "SurvivantApp/Inputs/InputManager.h"

#include <unordered_map>
#include "SurvivantCore/Events/Event.h"


namespace UI
{
	class EditorWindow : public App::Window
	{
	public:
		EditorWindow();
		~EditorWindow() = default;

		void StartRender() override;
		void RenderUI();
		void EndRender() override;
		bool ShouldClose() override;

		void SetupUI(EditorUI* p_ui);

	private:
		//init on creation
		EditorUI*	m_ui;
		bool		m_shouldClose = false; 

		//std::unordered_map<KeyboardKeyType, KeyCallback>
		std::unordered_map<App::InputManager::KeyboardKeyType, App::InputManager::KeyCallback> m_keyInputCallbacks;
	};
}
