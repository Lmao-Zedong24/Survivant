//Window.h
#pragma once

#include "SurvivantApp/Inputs/InputManager.h"
#include "SurvivantApp/Inputs/KeyboardInputs.h"

struct GLFWwindow;
struct GLFWmonitor;

namespace App
{
	constexpr const char* GLSL_Version = "#version 330"; //#version 330 core
	
	class Window
	{
	public:
		friend InputManager;

		Window();
		~Window();

		GLFWwindow* GetWindow();
		void ToggleFullScreenMode();

	private:
		void SetupInputManager() const;
		void GetMousePos(double& p_x, double& p_y) const;
		bool EvaluateInput(EKey p_key, EKeyState p_state, EInputModifier p_modif = static_cast<EInputModifier>(-1));
		bool EvaluateInput(EMouseButton p_button, EMouseButtonState p_state, EInputModifier p_modif = static_cast<EInputModifier>(-1));

		bool EvaluteModif(EInputModifier p_modif);
		EKey GetModifKey(EInputModifier p_modif);

		GLFWwindow*		m_window;
		GLFWmonitor*	m_monitor;

		bool	m_isInFullscreen;
		int		m_yWindowedPos;
	};
}


