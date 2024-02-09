//Window.h
#include "GLFW/glfw3.h"

namespace App
{
	class Window
	{
	public:
		Window();
		~Window();
		
		GLFWwindow* GetWindow();

	public:
		static void SetupInputManager(GLFWwindow* p_window);

	public:
		void ToggleFullScreenMode();

	private:
		GLFWwindow*		m_window;
		GLFWmonitor*	m_monitor;

		bool	m_isInFullscreen;
		int		m_yWindowedPos;
	};
}


