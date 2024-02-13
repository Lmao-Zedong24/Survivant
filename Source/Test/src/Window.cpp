//Window.cpp

#include "SurvivantCore/Debug/Assertion.h"
#include "SurvivantTest/Window.h"
#include "SurvivantTest/InputManager.h"

#include "GLFW/glfw3.h"
//#include "glad/gl.h"


using namespace App;

void InputManagerKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    window;
    //key;
    //scancode;
    //action;
    //mods;
    InputManager::GetInstance().CallInput(
        InputManager::KeyboardKeyType(
            static_cast<EKey>(key), 
            static_cast<EKeyState>(action), 
            static_cast<EInputModifier>(mods)), 
        static_cast<char>(scancode));

    //InputManager::GetInstance().CallInput(
    //    InputManager::KeyboardKeyType(
    //        EKey::KEY_B,
    //        EKeyState::KEY_PRESSED,
    //        EInputModifier()),
    //    static_cast<char>(scancode));
}  

void InputManagerMousCallback(GLFWwindow* window, int button, int action, int mods)
{
    window;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    InputManager::GetInstance().CallInput(
        InputManager::MouseKeyType(
            static_cast<EMouseButton>(button),
            static_cast<EMouseButtonState>(action),
            static_cast<EInputModifier>(mods)),
        static_cast<float>(xpos), 
        static_cast<float>(ypos));
}

Window::Window()
{


    //inputs
    //SetupInputManager();
}

Window::~Window()
{

}

//void App::Window::SetWindow(GLFWwindow* p_window)
//{
//    s_window = p_window;
//}
//
//GLFWwindow* App::Window::GetWindow()
//{
//    return s_window;
//}

void App::Window::SetupInputManager(GLFWwindow* p_window)
{
    glfwSetKeyCallback(p_window, InputManagerKeyCallback);
    glfwSetMouseButtonCallback(p_window, InputManagerMousCallback);
}

