//UI.cpp

#include "SurvivantUI/Menu.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

//#include "imgui_internal.h"



UI::Menu::Menu(const Menu& p_other)
{
    *this = p_other;
}

UI::Menu::Menu(Menu&& p_other)noexcept
{
    this->m_name = p_other.m_name;
    this->m_items = std::move(p_other.m_items);
}

UI::Menu& UI::Menu::operator=(const Menu& p_other)
{
    this->m_name = p_other.m_name;

    this->m_items.clear();
    this->m_items.reserve(p_other.m_items.size());
    for (const auto& item : p_other.m_items)
    {
        this->m_items.emplace_back();
        this->m_items.back().reset(item->Clone());
    }

    this->m_items.shrink_to_fit();

    return *this;
}

UI::IMenuable* UI::Menu::Clone() const
{
    return new Menu(*this);
}

void UI::Menu::DisplayAndUpdateMenu()
{
    DisplayAndUpdate();
}

void UI::Menu::DisplayAndUpdatePanel()
{
    DisplayAndUpdate();
}

void UI::Menu::SetName(const std::string& p_name)
{
    m_name = p_name;
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
            menu.DisplayAndUpdateMenu();

        ImGui::EndMenuBar();
    }
}