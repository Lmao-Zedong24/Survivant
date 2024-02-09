//Window.cpp

#include "SurvivantApp/Inputs/InputManager.h"
#include "SurvivantApp/Windows/Window.h"
#include "SurvivantCore/Debug/Assertion.h"

#include "GLFW/glfw3.h"
//#include "glad/gl.h"


using namespace App;

void InputManagerKeyCallback(GLFWwindow* /*p_window*/, int p_key, int p_scancode, int p_action, int p_mods)
{
    InputManager::GetInstance().CallInput(
        InputManager::KeyboardKeyType(
            static_cast<EKey>(p_key), 
            static_cast<EKeyState>(p_action), 
            static_cast<EInputModifier>(p_mods)), 
        static_cast<char>(p_scancode));
}  

void InputManagerMousCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
{
    double xpos, ypos;
    glfwGetCursorPos(p_window, &xpos, &ypos);

    InputManager::GetInstance().CallInput(
        InputManager::MouseKeyType(
            static_cast<EMouseButton>(p_button),
            static_cast<EMouseButtonState>(p_action),
            static_cast<EInputModifier>(p_mods)),
        static_cast<float>(xpos), 
        static_cast<float>(ypos));
}

Window::Window()
{
    m_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    m_window = glfwCreateWindow(mode->width, mode->height, "Window", nullptr, nullptr);
    m_isInFullscreen = false;

    int x;
    glfwGetWindowPos(m_window, &x, &m_yWindowedPos);
    glfwSetWindowPos(m_window, 0, m_yWindowedPos);

    glfwMakeContextCurrent(m_window);
}

App::Window::~Window()
{
    glfwDestroyWindow(m_window);
}

GLFWwindow* App::Window::GetWindow()
{
    return m_window;
}

void App::Window::SetupInputManager(GLFWwindow* p_window)
{
    glfwSetKeyCallback(p_window, InputManagerKeyCallback);
    glfwSetMouseButtonCallback(p_window, InputManagerMousCallback);
}

void App::Window::ToggleFullScreenMode()
{
    const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
    glfwSetWindowMonitor(
        m_window, 
        m_isInFullscreen? nullptr: m_monitor,
        0, 
        m_isInFullscreen? m_yWindowedPos: 0, 
        mode->width, 
        mode->height, 
        mode->refreshRate);

    m_isInFullscreen = !m_isInFullscreen;
}

