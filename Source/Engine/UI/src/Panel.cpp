//UI.cpp

#include "SurvivantUI/Panel.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui_internal.h"

const std::string& UI::Panel::GetName()
{
    return m_name;
}

UI::Panel::Panel(const std::string& p_name):
    m_name(p_name)
{}

std::string UI::Panel::GetUniqueName(const char p_name[], size_t p_count)
{
    return (p_name + (p_count > 0 ? "(" + std::to_string(p_count) + ")" : ""));
}
