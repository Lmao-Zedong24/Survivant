//Window.h
#include "GLFW/glfw3.h" // TODO : Get rid of glfw include in window header

namespace App
{
	class Window
	{
	public:
		Window();
		~Window();

		//void SetWindow(GLFWwindow* p_window);
		//GLFWwindow* GetWindow();

	public:
		static void SetupInputManager(GLFWwindow* p_window);

	private:
		static GLFWwindow* s_window;
	};
}


