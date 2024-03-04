//SubWindow.cpp

#include "imgui.h"
#include "SurvivantUI/SubWindow.h"

#include "SurvivantApp/Windows/Window.h"
#include "SurvivantCore/Events/EventManager.h"
#include "SurvivantUI/Panel.h"
#include "SurvivantUI/UI.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <algorithm>


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
    Panel(NAME),
    m_panelFlags(ERenderFlags())
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
            "Console",
            [this](char) { m_panelFlags = Panel::ERenderFlags(m_panelFlags | Panel::ERenderFlags::ADD_CONSOLE_PANNEL); }));
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

    m_panelFlags = ERenderFlags();
    m_menuBar.DisplayAndUpdatePanel();
    ImGui::End();

    return m_panelFlags;
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

UI::ConsolePanel::ConsolePanel() :
    m_filterMenu("Filters"),
    m_input("Input", PanelTextInput::ClearPanelText)
{
    static size_t NumLogTypes = 5;
    m_name = GetUniqueName(NAME, s_panelCount);
    s_panelCount++;

    m_textBox;
    m_buttons.m_buttons.emplace_back("Clear", [this]() { m_textBox.Clear(); });
    m_buttons.m_buttons.emplace_back("Copy", [this]() { m_textBox.Copy(); });

    m_currentFilters = std::vector<unsigned char>(NumLogTypes, static_cast<unsigned char>(false));
    for (size_t i = 0; i < NumLogTypes; i++)
    {
        ELogType type = ELogType(1 << i);
        //convert stored uchar to bool ref
        auto& boolRef = *(bool*)&(m_currentFilters[i]);

        m_filterMenu.m_items.emplace_back(
            std::make_unique<MenuCheckBox>(LogTypeToString(type), boolRef));
    }

    //debug event
    Core::EventManager::GetInstance().AddListenner<EditorUI::DebugEvent>(
        [this](const char* m_message) 
        { 
            if (this == nullptr)
                return;

            m_textBox.AddItem(
                std::make_shared<ConsolePanel::LogText>(LogInfo{ ELogType::DEBUG_LOG, m_message }));
        });
}

UI::ConsolePanel::~ConsolePanel()
{
    s_panelCount--;
}

Panel::ERenderFlags UI::ConsolePanel::Render()
{
    bool open;

    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin(m_name.c_str(), &open))
        return Panel::ERenderFlags();

    m_buttons.DisplayAndUpdatePanel();
    ImGui::Separator();

    std::vector<unsigned char> lastFilters = m_currentFilters;
    m_filterMenu.DisplayAndUpdatePanel();
    ImGui::Separator();

    for (size_t i = 0; i < m_currentFilters.size(); i++)
    {
        if (lastFilters[i] != m_currentFilters[i])
        {
            ELogType type = ELogType(1 << i);
            m_textBox.AddOrRemoveFilter(LogTypeToString(type));
        }
    }

    m_input.DisplayAndUpdatePanel();
    ImGui::Separator();
    m_textBox.DisplayAndUpdatePanel();

    ImGui::End();

    auto flags = ERenderFlags();
    if (!open)
        flags = ERenderFlags::CLOSE;

    return flags;
}

void UI::ConsolePanel::AddConsoleLog(const LogInfo& p_log)
{
    m_textBox.AddItem(std::make_shared<LogText>(p_log));
}

std::string UI::ConsolePanel::LogTypeToString(ELogType p_type)
{
    switch (p_type)
    {
    case UI::ConsolePanel::ELogType::DEBUG_LOG:
        return "[Debug]   ";
    case UI::ConsolePanel::ELogType::WARNING_LOG:
        return "[Warning] ";
    case UI::ConsolePanel::ELogType::ERROR_LOG:
        return "[ERROR]   ";
    case UI::ConsolePanel::ELogType::COMMAND_LOG:
        return "[Command] ";
    case UI::ConsolePanel::ELogType::DEFAULT_LOG:
    default:
        return "[Default] ";
    }
}

void UI::ConsolePanel::LogTypeColor(ELogType p_type, ImVec4* p_color)
{
    switch (p_type)
    {
    case UI::ConsolePanel::ELogType::DEBUG_LOG:
        *p_color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
        break;
    case UI::ConsolePanel::ELogType::WARNING_LOG:
        *p_color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        break;
    case UI::ConsolePanel::ELogType::ERROR_LOG:
        *p_color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        break;
    case UI::ConsolePanel::ELogType::COMMAND_LOG:
        *p_color = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
        break;
    case UI::ConsolePanel::ELogType::DEFAULT_LOG:
    default:
        p_color = nullptr;
        break;
    }
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
    if (m_buttons.empty())
        return;

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

void UI::PanelTextBox::DisplayAndUpdatePanel()
{
    auto& textList = m_filters.empty() ? m_items : m_filteredItems;

    //const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0 /*-footer_height_to_reserve*/), ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar))
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

        //copy
        if (m_copy)
            ImGui::LogToClipboard();

        for (auto& text : textList)
        {
            text->DisplayAndUpdatePanel();
        }

        if (m_copy)
            ImGui::LogFinish();

        //Scrolling
        if (m_scrollToBottom || (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);

        m_copy = false;
        m_scrollToBottom = false;

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();

    
}

void UI::PanelTextBox::SetFilters(const FilterSet& p_filters)
{
    for (auto& filter : p_filters)
    {
        //group all filters with the same lenght together
        auto& set = m_filters.try_emplace(filter.length(), FilterSet()).first->second;
        set.insert(filter);
    }

    UpdateFilteredItems();
}

void UI::PanelTextBox::AddFilter(const std::string& p_filter)
{
    //insert filter with others of same lenght
    auto& set = m_filters.try_emplace(p_filter.length(), FilterSet()).first->second;
    set.insert(p_filter);

    UpdateFilteredItems();
}

void UI::PanelTextBox::RemoveFilter(const std::string& p_filter)
{
    const auto& itt = m_filters.find(p_filter.length());

    //does nothing if does not contain filter
    if (itt == m_filters.end())
        return;

    //erase filter
    itt->second.erase(p_filter);

    //if set is empty, remove it from the map
    if (itt->second.empty())
        m_filters.erase(itt);

    UpdateFilteredItems();
}

void UI::PanelTextBox::AddOrRemoveFilter(const std::string& p_filter)
{
    const auto& itt = m_filters.find(p_filter.length());

    //add if doesnt contain
    if (itt == m_filters.end() || !itt->second.contains(p_filter))
    {
        auto& set = m_filters.try_emplace(p_filter.length(), FilterSet()).first->second;
        set.insert(p_filter);
    }
    //remove if contains
    else
        itt->second.erase(p_filter);

    UpdateFilteredItems();
}

void UI::PanelTextBox::AddItem(const std::shared_ptr<ITextable>& item, bool p_willScrollToBottom)
{
    m_items.push_back(item);

    if (IsFilteredItem(item.get()))
        m_filteredItems.push_back(item);

    m_scrollToBottom = p_willScrollToBottom;
}

void UI::PanelTextBox::Clear()
{
    m_items.clear();
    m_filteredItems.clear();
}

void UI::PanelTextBox::Copy()
{
    m_copy = true;
}

bool UI::PanelTextBox::IsFilteredItem(const ITextable* p_item)
{
    if (m_filters.empty())
        return false;

    bool isFiltered = false;
    size_t itemLen = p_item->GetLength();

    for (auto& pair : m_filters)
    {
        size_t filterLen = pair.first;

        if (isFiltered || itemLen < filterLen)
            continue;

        //isFiltered if item is equal to a filter
        auto& set = pair.second;
        isFiltered = set.contains(p_item->GetString(filterLen));
    }

    return isFiltered;
}

void UI::PanelTextBox::UpdateFilteredItems()
{
    m_filteredItems.clear();

    if (m_filters.empty())
        return;

    for (auto& item : m_items)
    {
        //add item if filtered
        if (IsFilteredItem(item.get()))
            m_filteredItems.push_back(item);
    }

}

UI::ConsolePanel::LogText::LogText(const LogInfo& p_logInfo) :
    m_logInfo(p_logInfo)
{
    m_length = GetString().length();
}

void UI::ConsolePanel::LogText::DisplayAndUpdatePanel()
{
    ImVec4 color;
    LogTypeColor(m_logInfo.m_type, &color);
    bool has_color = &color != nullptr;

    if (has_color)
        ImGui::PushStyleColor(ImGuiCol_Text, color);

    ImGui::TextUnformatted(LogTypeToString(m_logInfo.m_type).c_str());

    if (has_color)
        ImGui::PopStyleColor();

    ImGui::SameLine();
    ImGui::TextUnformatted((SPACER + m_logInfo.m_message).c_str());
}

std::string UI::ConsolePanel::LogText::GetString(size_t p_len)const
{
    if (p_len == 0)
        return  std::string((LogTypeToString(m_logInfo.m_type) + SPACER + m_logInfo.m_message));

    auto tmp = std::string((LogTypeToString(m_logInfo.m_type) + SPACER + m_logInfo.m_message), 0, p_len);
    return tmp;
}

size_t UI::ConsolePanel::LogText::GetLength()const
{
    return m_length;

}

UI::MenuCheckBox::MenuCheckBox(const std::string& p_name, bool& p_isChecked) :
    m_name(p_name),
    m_isCheked(&p_isChecked)
{
}

void UI::MenuCheckBox::DisplayAndUpdateMenu()
{
    if (ImGui::MenuItem(m_name.c_str(), nullptr, *m_isCheked, true))
        *m_isCheked = !(*m_isCheked);
}

struct InputTextCallback_UserData
{
    std::string* Str;
    ImGuiInputTextCallback  ChainCallback;
    void* ChainCallbackUserData;
};

//code from imgui_stdlib.cpp
int InputTextCallback(::ImGuiInputTextCallbackData* data)
{
    InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string callback
        // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
        std::string* str = user_data->Str;
        IM_ASSERT(data->Buf == str->c_str());
        str->resize(data->BufTextLen);
        data->Buf = (char*)str->c_str();
    }
    else if (user_data->ChainCallback)
    {
        // Forward to user callback, if any
        data->UserData = user_data->ChainCallbackUserData;
        return user_data->ChainCallback(data);
    }
    return 0;
}

//code from imgui_stdlib.cpp
bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = callback;
    cb_user_data.ChainCallbackUserData = user_data;

    using namespace std::placeholders;

    return ImGui::InputText(
        label, (char*)str->c_str(), str->capacity() + 1, flags,
        InputTextCallback,
        &cb_user_data);
}

UI::PanelTextInput::PanelTextInput(std::string p_name, std::function<void(PanelTextInput&)> p_callback) :
    m_name(p_name),
    m_callback(p_callback)
{
}

void UI::PanelTextInput::DisplayAndUpdatePanel()
{
    //Command-line
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = 
        ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | 
        ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    InputText(m_name.c_str(), &m_buffer, input_text_flags, TextPanelCallBack, (void*)this);
}

void UI::PanelTextInput::Clear()
{
    m_buffer.clear();
}

const std::string& UI::PanelTextInput::GetText() const
{
    return m_buffer;
}

void UI::PanelTextInput::ClearPanelText(PanelTextInput& p_panel)
{
    p_panel.Clear();
}

int UI::PanelTextInput::TextPanelCallBack(ImGuiInputTextCallbackData* data)
{
    //? imgui magic
    PanelTextInput* panelText = (PanelTextInput*)data->UserData;
    panelText->m_callback(*panelText);

    return 0;
}


