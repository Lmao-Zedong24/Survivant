//Window.cpp

#include "SurvivantApp/Inputs/InputManager.h"
#include "SurvivantApp/Windows/Window.h"
#include "SurvivantCore/Debug/Assertion.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

using namespace App;

void IMKeyCallback(GLFWwindow* /*p_window*/, int p_key, int p_scancode, int p_action, int p_mods)
{
    InputManager::GetInstance().CallInput(
        InputManager::KeyboardKeyType(
            static_cast<EKey>(p_key), 
            static_cast<EKeyState>(p_action), 
            static_cast<EInputModifier>(p_mods)), 
        static_cast<char>(p_scancode));
}  

void IMMouseCallback(GLFWwindow* p_window, int p_button, int p_action, int p_mods)
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

void WindowCloseCallback(GLFWwindow* /*window*/)
{
    Core::EventManager::GetInstance().Invoke<Window::WindowCloseRequest>();
}

void WindowSizeCallback(GLFWwindow* /*window*/, int p_width, int p_height)
{
    Core::EventManager::GetInstance().Invoke<Window::OnWindowSize>(p_width, p_height);
}


void WindowFramebufferSizeCallback(GLFWwindow* /*window*/, int p_width, int p_height)
{
    glViewport(0, 0, p_width, p_height);
    Core::EventManager::GetInstance().Invoke<Window::OnFrameBufferSize>(p_width, p_height);
}


void WindowContentScaleCallback(GLFWwindow* /*window*/, float p_xscale, float p_yscale)
{
    Core::EventManager::GetInstance().Invoke<Window::OnWindowContentScale>(p_xscale, p_yscale);
}

void WindowMinimizeCallback(GLFWwindow* /*window*/, int iconified)
{
    Core::EventManager::GetInstance().Invoke<Window::WindowMinimize>(iconified != 0);
}

Window::Window(std::string p_name)
{
    //init
    m_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    m_glfwWindow = glfwCreateWindow(mode->width, mode->height, p_name.c_str(), nullptr, nullptr);
    m_isInFullscreen = false;

    int x;
    glfwGetWindowPos(m_glfwWindow, &x, &m_yWindowedPos);
    glfwSetWindowPos(m_glfwWindow, 0, m_yWindowedPos);

    glfwMakeContextCurrent(m_glfwWindow);
}

App::Window::Window(std::string p_name, int p_width, int p_height, int p_x, int p_y)
{
    //init
    m_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    m_glfwWindow = glfwCreateWindow(p_width, p_height, p_name.c_str(), nullptr, nullptr);
    m_isInFullscreen = false;

    glfwSetWindowPos(m_glfwWindow, p_x, p_y);
    glfwMakeContextCurrent(m_glfwWindow);

    m_yWindowedPos = p_y;
}

App::Window::~Window()
{
    glfwDestroyWindow(m_glfwWindow);
}

GLFWwindow* App::Window::GetWindow()
{
    return m_glfwWindow;
}

void App::Window::SetupWindowCallbacks() const
{
    glfwSetWindowCloseCallback(m_glfwWindow, WindowCloseCallback);
    glfwSetWindowSizeCallback(m_glfwWindow, WindowSizeCallback);
    glfwSetFramebufferSizeCallback(m_glfwWindow, WindowFramebufferSizeCallback);
    glfwSetWindowIconifyCallback(m_glfwWindow, WindowMinimizeCallback);
}

void App::Window::SetupInputManagerCallbacks() const
{
    glfwSetKeyCallback(m_glfwWindow, IMKeyCallback);
    glfwSetMouseButtonCallback(m_glfwWindow, IMMouseCallback);

}

void App::Window::GetMousePos(double& p_x, double& p_y) const
{
    glfwGetCursorPos(m_glfwWindow, &p_x, &p_y);
}

void App::Window::GetWindowSize(int& p_width, int& p_height) const
{
    glfwGetWindowSize(m_glfwWindow, &p_width, &p_height);
}

bool App::Window::EvaluateInput(EKey p_key, EKeyState p_state, EInputModifier p_modif)
{
    return  static_cast<int>(p_state) == glfwGetKey(m_glfwWindow, static_cast<int>(p_key)) &&
            EvaluteModif(p_modif);
}

bool App::Window::EvaluateInput(EMouseButton p_button, EMouseButtonState p_state, EInputModifier p_modif)
{
    return  static_cast<int>(p_state) == glfwGetMouseButton(m_glfwWindow, static_cast<int>(p_button)) &&
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
        int state = glfwGetKey(m_glfwWindow, static_cast<int>(InputManager::GetModifKey(static_cast<EInputModifier>(modif))));
        if (state == static_cast<int>(EKeyState::PRESSED))
            currentModif += modif;
    }

    return disiredModif == currentModif;
}

void App::Window::ToggleFullScreenMode()
{
    const GLFWvidmode* mode = glfwGetVideoMode(m_monitor);
    glfwSetWindowMonitor(
        m_glfwWindow, 
        m_isInFullscreen? nullptr: m_monitor,
        0, 
        m_isInFullscreen? m_yWindowedPos: 0, 
        mode->width, 
        mode->height, 
        mode->refreshRate);

    m_isInFullscreen = !m_isInFullscreen;
}

void App::Window::StartRender()
{
    glfwPollEvents();
}


void App::Window::EndRender()
{
    glfwSwapBuffers(m_glfwWindow);
}

bool App::Window::ShouldClose()
{
    return glfwWindowShouldClose(m_glfwWindow);
}

void App::Window::SetWindowSizeLimits(int p_minWidth, int p_minHeight, int p_maxWidth, int p_maxHeight)
{
    glfwSetWindowSizeLimits(m_glfwWindow, p_minWidth, p_minHeight, p_maxWidth, p_maxHeight);
}

void App::Window::SetAspectRatio(int p_width, int p_height)
{
    glfwSetWindowAspectRatio(m_glfwWindow, p_width, p_height);
}

void App::Window::SetWindowIcons(std::vector<GLFWimage> p_images)
{
    glfwSetWindowIcon(m_glfwWindow, static_cast<int>(p_images.size()), p_images.data());
}

void App::Window::SetFocusWindow()
{
    glfwFocusWindow(m_glfwWindow);
}

void App::Window::WindowCloseRequest::BeforeInvoke()
{
    m_cancelRequest = false;
}

void App::Window::WindowCloseRequest::AfterInvoke()
{
    if (!m_cancelRequest)
        Core::EventManager::GetInstance().Invoke<WindowClosing>();
}

void App::Window::WindowCloseRequest::InterceptCloseRequest()
{
    m_cancelRequest = true;
}
