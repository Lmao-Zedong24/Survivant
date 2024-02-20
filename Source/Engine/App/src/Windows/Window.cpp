//Window.cpp

#include "SurvivantApp/Inputs/InputManager.h"
#include "SurvivantApp/Windows/Window.h"
#include "SurvivantCore/Debug/Assertion.h"

#include "GLFW/glfw3.h"

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

void InputManagerMouseCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
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

    //call inputs form manager
    //SetupInputManager();
}

App::Window::~Window()
{
    glfwDestroyWindow(m_window);
}

GLFWwindow* App::Window::GetWindow()
{
    return m_window;
}

void App::Window::SetupInputManager() const
{
    glfwSetKeyCallback(m_window, InputManagerKeyCallback);
    glfwSetMouseButtonCallback(m_window, InputManagerMouseCallback);
}

void App::Window::GetMousePos(double& p_x, double& p_y) const
{
    glfwGetCursorPos(m_window, &p_x, &p_y);
}

bool App::Window::EvaluateInput(EKey p_key, EKeyState p_state, EInputModifier p_modif)
{
    return  static_cast<int>(p_state) == glfwGetKey(m_window, static_cast<int>(p_key)) &&
            EvaluteModif(p_modif);
}

bool App::Window::EvaluateInput(EMouseButton p_button, EMouseButtonState p_state, EInputModifier p_modif)
{
    return  static_cast<int>(p_state) == glfwGetMouseButton(m_window, static_cast<int>(p_button)) &&
            EvaluteModif(p_modif);
}

bool App::Window::EvaluteModif(EInputModifier p_modif)
{
    int disiredModif = static_cast<int>(p_modif);
    int currentModif = 0;

    if (disiredModif < 0)
        return true;

    for (size_t i = 0; i < NUM_INPUT_MODIFIERS; i++)
    {
        int modif = 1 << i;
        int state = glfwGetKey(m_window, static_cast<int>(GetModifKey(static_cast<EInputModifier>(modif))));
        if (state == static_cast<int>(EKeyState::KEY_PRESSED))
            currentModif += modif;
    }

    return disiredModif == currentModif;
}

EKey App::Window::GetModifKey(EInputModifier p_modif)
{
    //gotat put this if I want to use enum
#undef MOD_SHIFT
#undef MOD_CONTROL
#undef MOD_ALT
    switch (p_modif)
    {
    case App::EInputModifier::MOD_SHIFT:
        return EKey::KEY_LEFT_SHIFT;
    case App::EInputModifier::MOD_CONTROL:
        return EKey::KEY_LEFT_CONTROL;
    case App::EInputModifier::MOD_ALT:
        return EKey::KEY_LEFT_ALT;
    case App::EInputModifier::MOD_SUPER:
        return EKey::KEY_LEFT_SUPER;
    case App::EInputModifier::MOD_CAPS_LOCK:
        return EKey::KEY_CAPS_LOCK;
    case App::EInputModifier::MOD_NUM_LOCK:
        return EKey::KEY_NUM_LOCK;
    default:
        return EKey();
    }
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

