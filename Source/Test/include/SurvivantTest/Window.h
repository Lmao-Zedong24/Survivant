//Window.h
#include "GLFW/glfw3.h"

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


