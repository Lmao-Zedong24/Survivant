//Window.h
#pragma once

struct GLFWwindow;
struct GLFWmonitor;

namespace App
{
	constexpr const char* GLSL_Version = "#version 330"; //#version 330 core
	
	class Window
	{
	public:
		Window();
		~Window();

		GLFWwindow* GetWindow();
		void ToggleFullScreenMode();

	private:
		void SetupInputManager();
		void GetMousePos(double& p_x, double& p_y);

		GLFWwindow*		m_window;
		GLFWmonitor*	m_monitor;

		bool	m_isInFullscreen;
		int		m_yWindowedPos;
	};
}


