//Window.h
#pragma once

#include "SurvivantApp/Inputs/InputManager.h"
#include "SurvivantApp/Inputs/KeyboardInputs.h"
#include "SurvivantCore/Events/Event.h"

#include <string>

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWimage;

namespace App
{
	constexpr const char* GLSL_Version = "#version 330"; //#version 330 core
	
	class Window
	{
	public:
		friend InputManager;

		//Window Events

		//TODO: remove this

		/// <summary>
		/// Request to close window
		/// </summary>	
		class WindowCloseRequest : public Core::Event<> 
		{
		public:
			void BeforeInvoke() override;
			void AfterInvoke() override;

			static void InterceptCloseRequest();

		private:
			static inline bool m_cancelRequest = false;
		};

		/// <summary>
		/// Request to close window
		/// </summary>	
		class WindowClosing : public Core::Event<> {};

		/// <summary>
		/// (width, height)
		/// </summary>
		class OnWindowSize : public Core::Event<int, int> {};

		/// <summary>
		/// (width, height) //TODO: unit/ de mesure
		/// </summary>	
		class OnFrameBufferSize : public Core::Event<int, int> {};

		/// <summary>
		/// Ratio between the current DPI and the platform's default DPI (xscale, yscale)
		/// </summary>
		class OnWindowContentScale : public Core::Event<float, float> {};

		/// <summary>
		/// (isMinimized)
		/// </summary>
		class WindowMinimize : public Core::Event<bool> {};


		Window(std::string p_name = "Window");
		Window(std::string p_name, int p_width, int p_height, int p_x, int p_y);
		~Window();

		GLFWwindow* GetWindow();
		void ToggleFullScreenMode();

		virtual void StartRender();
		virtual void EndRender();
		virtual bool ShouldClose();


		/// <summary>
		/// Set min/max window size, or -1 for no limits
		/// </summary>
		void SetWindowSizeLimits(int p_minWidth = 0, int p_minHeight = 0, int p_maxWidth = -1, int p_maxHeight = -1);

		/// <summary>
		/// Set fixed Aspect Ratio, or -1 fot no fixed value
		/// </summary>
		void SetAspectRatio(int p_width, int p_height);

		/// <summary>
		/// Set top-left window icon with list of candidates
		/// </summary>
		void SetWindowIcons(std::vector<GLFWimage> p_images);

		void SetFocusWindow();

		int GetTextureId() { return m_textureId; };
		static inline int m_textureId = 0;

	protected:
		void SetupWindowCallbacks()const;
		void SetupInputManagerCallbacks() const;
		void GetMousePos(double& p_x, double& p_y) const;

		void GetWindowSize(int& p_width, int& p_height) const;

		bool EvaluateInput(EKey p_key, EKeyState p_state, EInputModifier p_modif = static_cast<EInputModifier>(-1));
		bool EvaluateInput(EMouseButton p_button, EMouseButtonState p_state, EInputModifier p_modif = static_cast<EInputModifier>(-1));

		bool EvaluteModif(EInputModifier p_modif);

		GLFWwindow*		m_glfwWindow;
		GLFWmonitor*	m_monitor;

		bool	m_isInFullscreen;
		int		m_yWindowedPos;
	};
}


