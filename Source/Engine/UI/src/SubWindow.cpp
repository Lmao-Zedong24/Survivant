//SubWindow.cpp

#include "SurvivantUI/SubWindow.h"

#include "SurvivantApp/Windows/Window.h"
#include "SurvivantCore/Events/EventManager.h"
#include "SurvivantUI/Panel.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


using namespace UI;

Panel::ERenderFlags UI::ImagePanel::Render()
{
    static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
    bool showWindow = true;

    ImGui::Begin(m_name.c_str(), &showWindow, window_flags);
    
    ImGui::Image((void*)m_textureId, ImGui::GetWindowSize());
    ImGui::End();


    ERenderFlags flags = ERenderFlags();
    if (!showWindow)
        flags = ERenderFlags(flags | ERenderFlags::CLOSE);

   return flags;
}

Panel::ERenderFlags UI::TestPanel::Render()
{
    bool showWindow = true;

    ImGui::Begin(m_name.c_str(), &showWindow);
    ImGui::Text("TESSSSSSSSSSSSTTTTTTTTTT");
    if (ImGui::Button("Close Me"))
        showWindow = false;

    ImGui::End();

    ERenderFlags flags = ERenderFlags();
    if (!showWindow)
        flags = ERenderFlags(flags | ERenderFlags::CLOSE);

    return flags;
}

UI::MainPanel::MainPanel() :
    Panel(NAME)
{
    using namespace App;
    auto& menuList = m_menuBar.m_menus;

    //add menu 'File' to menu list
    Menu& menu1 = menuList.emplace_back("File");
    //add buttons to menu that triggers an event
    menu1.m_items.emplace_back(std::make_unique<MenuButton>(
        "New", 
        [](char) { }));
    //add buton with a keyboard shortcut
    menu1.m_items.emplace_back(std::make_unique<MenuButton>(
        "Exit", 
        [](char) { Core::EventManager::GetInstance().Invoke<App::Window::WindowCloseRequest>(); },
        InputManager::KeyboardKeyType(
            EKey::KEY_F11,
            EKeyState::KEY_PRESSED,
            EInputModifier::MOD_ALT)
    ));

    Menu& menu2 = menuList.emplace_back("Edit");
    menu2.m_items.emplace_back(std::make_unique<MenuButton>(
        "Button1",
        [](char) {  },
        InputManager::KeyboardKeyType(
            EKey::KEY_F11,
            EKeyState::KEY_PRESSED,
            EInputModifier(EInputModifier::MOD_ALT | EInputModifier::MOD_CONTROL))
    ));
    menu2.m_items.emplace_back(std::make_unique<MenuButton>(
        "Cut",
        [](char) {}));
    menu2.m_items.emplace_back(std::make_unique<MenuButton>(
        "Copy",
        [](char) {}));
    menu2.m_items.emplace_back(std::make_unique<MenuButton>(
        "Paste",
        [](char) {}));
    menu2.m_items.emplace_back(std::make_unique<MenuButton>(
        "Undo",
        [](char) {}));
    //Add a menu to the menu
    {
        auto menu3 = std::make_unique<Menu>("View");
        menu3->m_items.emplace_back(std::make_unique<MenuButton>(
            "Window1",
            [](char) {}));
        menu3->m_items.emplace_back(std::make_unique<MenuButton>(
            "Window2",
            [](char) {}));
        menu3->m_items.emplace_back(std::make_unique<MenuButton>(
            "Window3",
            [](char) {}));

        menu2.m_items.emplace_back(std::move(menu3));
    }
   
}

Panel::ERenderFlags UI::MainPanel::Render()
{
    static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

    bool open = true;
    //fullscreen + undockable/cant move
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    //always begin bcs if not lose docked childreen
    ImGui::Begin("DockSpace Demo", &open, windowFlags);

    //?
    ImGui::PopStyleVar(2);

    // Submit the DockSpace
    ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

    if (m_layout)
        SetupLayout(static_cast<int>(dockspaceId));

    //ERenderFlags panelFlags = ERenderFlags();
    m_menuBar.DisplayAndUpdatePanel();
    ImGui::End();

    return ERenderFlags();
}

void UI::MainPanel::ChangePanelLayout(const ChangeLayout& p_layout)
{
    m_layout = p_layout;
}

void UI::MainPanel::SetupLayout(int p_dockspaceId)
{
    m_layout(p_dockspaceId);
    m_layout = nullptr;
}

UI::InspectorPanel::InspectorPanel()
{
    m_name = GetUniqueName(NAME, s_panelCount);
    s_panelCount++;
}

UI::InspectorPanel::~InspectorPanel()
{
    s_panelCount--;
}

Panel::ERenderFlags UI::InspectorPanel::Render()
{
    bool open;
    ImGui::Begin("DockSpace Demo", &open);

    ERenderFlags panelFlags = ERenderFlags();

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            

            if (ImGui::MenuItem("NEW WINDOW", "", false, true))
                panelFlags = ERenderFlags(panelFlags | ERenderFlags::ADD_TEST_PANNEL);

            ImGui::Separator();
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();

    return ERenderFlags();
}

UI::MenuButton::MenuButton(const std::string& p_name, const App::InputManager::KeyCallback& p_callback) :
    IMenuable()
{
    m_name = p_name;
    m_callback = p_callback;
}

UI::MenuButton::MenuButton(
    const std::string& p_name, 
    const App::InputManager::KeyCallback& p_callback, 
    const App::InputManager::KeyboardKeyType& p_shortcut) :
    MenuButton(p_name, p_callback)
{
    AddShortcut(p_shortcut);
}

void UI::MenuButton::DisplayAndUpdateMenu()
{
    if (ImGui::MenuItem(m_name.c_str(), m_shortcut.c_str(), false, true))
        m_callback(0);
}

void UI::MenuButton::AddShortcut(const App::InputManager::KeyboardKeyType& p_shortcut)
{
    auto& im = App::InputManager::GetInstance();
    im.AddInputBinding(p_shortcut, m_callback);
    m_shortcut = im.KeyBindingToString(p_shortcut);
}


void UI::PanelButton::DisplayAndUpdatePanel()
{
    if (ImGui::SmallButton(m_name.c_str()))
        m_callback();
}

void UI::PanelButtonList::DisplayAndUpdatePanel()
{
    auto buttonItt = m_buttons.begin();
    buttonItt->DisplayAndUpdatePanel();
    buttonItt++;

    for (auto& itt = buttonItt; itt != m_buttons.end(); itt++)
    {
        ImGui::SameLine();
        itt->DisplayAndUpdatePanel();
    }
}

UI::SavePanel::SavePanel()
{
    m_name = GetUniqueName(NAME, s_panelCount);
    s_panelCount++;

    m_options.m_buttons.push_back(PanelButton("Save", 
        []() { Core::EventManager::GetInstance().Invoke<App::Window::WindowClosing>(); }));
    m_options.m_buttons.push_back(PanelButton("Don't Save", 
        []() { Core::EventManager::GetInstance().Invoke<App::Window::WindowClosing>(); }));
    m_options.m_buttons.push_back(PanelButton("Close", 
        [this]() { m_open = false; }));
}

UI::SavePanel::~SavePanel()
{
    s_panelCount--;
}

Panel::ERenderFlags UI::SavePanel::Render()
{
    ImGui::Begin(m_name.c_str(), &m_open);

    //buttons or 'x' can close
    m_options.DisplayAndUpdatePanel();

    ImGui::End();

    ERenderFlags flags = ERenderFlags();
    if (!m_open)
        flags = ERenderFlags(flags | ERenderFlags::CLOSE);

    return flags;
}

