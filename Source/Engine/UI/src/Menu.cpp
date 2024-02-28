//UI.cpp

#include "SurvivantUI/Menu.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

//#include "imgui_internal.h"



UI::Menu::Menu(Menu&& p_other)noexcept
{
    this->m_name = p_other.m_name;
    this->m_items = std::move(p_other.m_items);
}

void UI::Menu::DisplayAndUpdatePanel()
{
    DisplayAndUpdate();
}

void UI::Menu::DisplayAndUpdateMenu()
{
    DisplayAndUpdate();
}

void UI::Menu::DisplayAndUpdate()
{
    if (ImGui::BeginMenu(m_name.c_str()))
    {
        for (auto& menu : m_items)
            menu->DisplayAndUpdateMenu();

        ImGui::EndMenu();
    }
}

void UI::MenuBar::DisplayAndUpdatePanel()
{
    if (ImGui::BeginMenuBar())
    {
        for (auto& menu : m_menus)
            menu.DisplayAndUpdatePanel();

        ImGui::EndMenuBar();
    }
}