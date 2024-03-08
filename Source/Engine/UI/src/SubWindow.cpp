//SubWindow.cpp

#include "SurvivantUI/SubWindow.h"

#include "SurvivantApp/Windows/Window.h"
#include "SurvivantCore/Events/EventManager.h"
#include "SurvivantUI/Panel.h"
#include "SurvivantUI/UI.h"

#include "imgui.h"
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

void tmpCallback(PanelTreeBranch& /*p_branch*/)
{
    std::string str = "Tree callback works";
    //p_branch.ForceCloseChildreen();
    Core::EventManager::GetInstance().Invoke<UI::EditorUI::DebugEvent>(str.c_str());
}

UI::TestPanel::TestPanel(const std::string& p_name) :
    Panel(p_name),
    m_unique("UNIQUE", { "Opt 1", "Opt 2", "Opt 3" }, nullptr),
    m_multiple("MULTIPLE", { "Opt 1", "Opt 2", "Opt 3" }, nullptr)
{}

Panel::ERenderFlags UI::TestPanel::Render()
{
    bool showWindow = true;

    ImGui::Begin(m_name.c_str(), &showWindow);
    ImGui::Text("TESSSSSSSSSSSSTTTTTTTTTT");
    if (ImGui::Button("Close Me"))
        showWindow = false;


    m_unique.DisplayAndUpdatePanel();
    m_multiple.DisplayAndUpdatePanel();

    ImGui::End();

    ERenderFlags flags = ERenderFlags();
    if (!showWindow)
        flags = ERenderFlags(flags | ERenderFlags::CLOSE);

    return flags;
}

UI::MainPanel::MainPanel() :
    Panel(NAME),
    m_panelFlags(ERenderFlags()),
    m_menuBar()
{}

UI::MainPanel::MainPanel(MenuBar&& p_menuBar) :
    Panel(NAME),
    m_panelFlags(ERenderFlags()),
    m_menuBar()
{
    SetMenuBar(std::move(p_menuBar));
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

void UI::MainPanel::SetMenuBar(MenuBar&& p_menuBar)
{
    m_menuBar = std::move(p_menuBar);
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
    m_input("Input", std::bind(&ConsolePanel::TextInputCallback, this, std::placeholders::_1))
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
    //m_eventHandle = 

    m_eventHandle = Core::EventManager::GetInstance().AddListenner<EditorUI::DebugEvent>(
        [this](const char* m_message)
        {
            if (this == nullptr)
                return;

            m_textBox.AddItem(
                std::make_shared<ConsolePanel::LogText>(LogInfo{ ELogType::DEBUG_LOG, m_message }));
        }
    );
}

UI::ConsolePanel::~ConsolePanel()
{
    s_panelCount--;
    Core::EventManager::GetInstance().RemoveListenner<EditorUI::DebugEvent>(m_eventHandle);
}

Panel::ERenderFlags UI::ConsolePanel::Render()
{
    bool open;

    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

    if (!ImGui::Begin(m_name.c_str(), &open))
    {
        ImGui::End();
        return Panel::ERenderFlags();
    }

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
    //case UI::ConsolePanel::ELogType::COMMAND_LOG:
    //    return "[Command] ";
    case UI::ConsolePanel::ELogType::DEFAULT_LOG:
    default:
        return "          ";
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
    //case UI::ConsolePanel::ELogType::COMMAND_LOG:
    //    *p_color = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
        //break;
    case UI::ConsolePanel::ELogType::DEFAULT_LOG:
    default:
        p_color = nullptr;
        break;
    }
}

void UI::ConsolePanel::TextInputCallback(PanelTextInput& p_textInput)
{
    m_textBox.AddItem(std::make_shared<LogText>(LogInfo{ ELogType::WARNING_LOG, p_textInput.GetText() }), true);
    p_textInput.Clear();
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

IMenuable* UI::MenuButton::Clone() const
{
    return new MenuButton(*this);
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
    if (ImGui::Begin(m_name.c_str(), &m_open))
    {
        //buttons or 'x' can close
        m_options.DisplayAndUpdatePanel();
    }


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

IMenuable* UI::MenuCheckBox::Clone() const
{
    return new MenuCheckBox(*this);
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

    if(InputText(m_name.c_str(), &m_buffer, input_text_flags, nullptr, (void*)this))
    {
        //when iconTxt is finished being inputed
        m_callback(*this);
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
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

UI::PanelUniqueSelection::PanelUniqueSelection(
    std::string p_name,
    std::vector<std::string> p_selectable, 
    std::function<void(int)> p_callback) :
    m_name(p_name),
    m_callback(p_callback)
{
    m_curentSelection = 0;
    m_count = static_cast<int>(p_selectable.size());

    for (auto& item : p_selectable)
        m_items += (item + '\0');
}

void UI::PanelUniqueSelection::DisplayAndUpdatePanel()
{
    if (ImGui::Combo(m_name.c_str(), &m_curentSelection, m_items.c_str()) && m_callback != nullptr)
        m_callback(m_curentSelection);
}

UI::PanelMultipleSelection::PanelMultipleSelection(
    std::string p_name, 
    std::vector<std::string> p_selectable, 
    std::function<void(int)> p_callback) :
    m_name(p_name),
    m_callback(p_callback)
{
    m_curentSelection = 0;
    m_count = static_cast<int>(p_selectable.size());

    m_items = p_selectable;
}

void UI::PanelMultipleSelection::DisplayAndUpdatePanel()
{
    auto oldSelection = m_curentSelection;

    if (ImGui::BeginCombo(m_name.c_str(), GetDisplayString().c_str()))
    {
        for (int i = 0; i < m_items.size(); i++)
        {
            int flag = 1 << i;
            bool is_selected = (m_curentSelection & flag);

            if (ImGui::Selectable(m_items[i].c_str(), is_selected, ImGuiSelectableFlags_DontClosePopups))
            {
                if (is_selected)
                    m_curentSelection &= ~flag;
                else
                    m_curentSelection |= flag;
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (oldSelection != m_curentSelection && m_callback != nullptr)
        m_callback(m_curentSelection);
}

std::string UI::PanelMultipleSelection::GetDisplayString()
{
    static const char* Seperator = ", ";
    static const char* EmptyString = "(none)";
    std::string str;
    size_t count = 0;
    
    for (size_t i = 0; i < m_items.size(); i++)
    {
        int flag = 1 << i;
        if (m_curentSelection & flag)
        {
            if (count++ > 0)
                str += Seperator;

            str += (m_items[i]);
        }
    }

    return str.empty() ? EmptyString : str;
}

UI::ContentDrawerPanel::ContentDrawerPanel() :
    m_tree()
{
    m_name = GetUniqueName(NAME, s_panelCount);
    //m_tree = std::make_shared<PanelTreeBranch>("TREE");

  /*  auto& branches = m_tree->SetBranches({ std::make_shared<PanelTreeBranch>("0"), std::make_shared<PanelTreeBranch>("1"), std::make_shared<PanelTreeBranch>("2") });
    branches["0"]->SetBranches({
        std::make_shared<PanelTreeBranch>("A-123456789"), 
        std::make_shared<PanelTreeBranch>("B-45678"), 
        std::make_shared<PanelTreeBranch>("B-45678"), 
        std::make_shared<PanelTreeBranch>("B-45678"), 
        std::make_shared<PanelTreeBranch>("B-45678"), 
        std::make_shared<PanelTreeBranch>("B-45678"), 
        std::make_shared<PanelTreeBranch>("B-45678"), 
        std::make_shared<PanelTreeBranch>("B-45678"), 
        std::make_shared<PanelTreeBranch>("B-45678"), 
        std::make_shared<PanelTreeBranch>("C") 
        });
    branches["1"]->SetBranches({std::make_shared<PanelTreeBranch>("D-123456789"), std::make_shared<PanelTreeBranch>("E-45678"), std::make_shared<PanelTreeBranch>("F")});
    branches["2"]->SetBranches({std::make_shared<PanelTreeBranch>("G-123456789"), std::make_shared<PanelTreeBranch>("H-45678"), std::make_shared<PanelTreeBranch>("I")});*/

    SetupTree();

    auto setGridDisplayFunc = std::make_shared<PanelTreeBranch::BranchCallback>(
        std::bind(&ContentDrawerPanel::SetGridDisplay, this, std::placeholders::_1));
    m_tree.get()->SetAllBranchesOnClickCallback(setGridDisplayFunc);

    auto tryOpenFileFunc = std::make_shared<PanelTreeBranch::BranchCallback>(
        std::bind(&ContentDrawerPanel::TryOpenFile, this, std::placeholders::_1));
    m_tree.get()->SetAllLeavesOnClickCallback(tryOpenFileFunc);

    s_panelCount++;
}

UI::ContentDrawerPanel::~ContentDrawerPanel()
{
    s_panelCount--;
}

Panel::ERenderFlags UI::ContentDrawerPanel::Render()
{
    static bool open = true;
    static float treeWidth = ImGui::GetContentRegionAvail().x * 0.5f;

    auto panelSize = ImGui::GetContentRegionAvail();
    ImGuiWindowFlags    window_flags = ImGuiWindowFlags_None;
    ImGuiChildFlags     child_flags = ImGuiChildFlags_AlwaysAutoResize | ImGuiChildFlags_AutoResizeY;

    if (!ImGui::Begin(m_name.c_str(), &open))
    {
        ImGui::End();
        return Panel::ERenderFlags();
    }

    //tree
    {
        if (ImGui::BeginChild("ChildL", ImVec2(treeWidth, ImGui::GetContentRegionAvail().y), child_flags, window_flags))
            m_tree.get()->DisplayAndUpdatePanel();
        
        ImGui::EndChild();
    }

    ImGui::SameLine();
    auto pos = ImGui::GetCursorPos();
    ImGui::Button("##", ImVec2(5, ImGui::GetContentRegionAvail().y));
    if (ImGui::IsItemHovered())
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
    }

    if (ImGui::IsItemActive())
    {
        treeWidth += ImGui::GetIO().MouseDelta.x;
        treeWidth = std::clamp(treeWidth, 10.0f, 2 * panelSize.x);
    }

    ImGui::SameLine();

    //grid
    {
        if (ImGui::BeginChild("ChildR", ImVec2(0, ImGui::GetContentRegionAvail().y), child_flags, window_flags))
            m_grid.DisplayAndUpdatePanel();
        ImGui::EndChild();
    }

    ImGui::End();

    auto flags = ERenderFlags();
    if (!open)
        flags = ERenderFlags::CLOSE;

    return flags;
}

bool UI::ContentDrawerPanel::SetGridDisplay(PanelTreeBranch& p_branch)
{
    p_branch.ForceOpenParents();
    auto& childreen = p_branch.GetChildreen();

    //"cast" from PanelTreeBranch to ISelectionBoxable
    std::vector<std::shared_ptr<ISelectionBoxable>> gridItems;
    gridItems.reserve(childreen.size());
    
    for (auto& pair : childreen)
        gridItems.emplace_back(pair.second);

    m_grid.SetSelectionBoxable(gridItems);

    //cannt display other items bcs changes them
    return true;
}

void UI::ContentDrawerPanel::SetupTree()
{

    auto root = std::filesystem::current_path();
    m_tree = std::make_shared<PanelTreeBranch>(root.filename().string());

    //auto files = directory_iterator(root);

    SetupBranches(m_tree, root);

}

void UI::ContentDrawerPanel::SetupBranches(
    std::shared_ptr<PanelTreeBranch> p_parent, const std::filesystem::path& p_filePath)
{
    using directory_iterator = std::filesystem::directory_iterator;
    using directory_ptr_and_path = std::pair<std::shared_ptr<PanelTreeBranch>, std::filesystem::path>;

    std::vector<directory_ptr_and_path> directories;

    for (const auto& dirEntry : directory_iterator(p_filePath))
    {
        const auto& path = dirEntry.path();
        std::string name = path.filename().string();

        auto ptrBranch = std::make_shared<PanelTreeBranch>(path.filename().string());
        p_parent.get()->AddBranch(ptrBranch);

        if (dirEntry.is_directory())
            directories.push_back({ ptrBranch, path });
    }

    for (auto& pair : directories)
        SetupBranches(pair.first, pair.second);

    //for (auto& child : files)
    //    p_parent.get()->AddBranch(std::make_shared<PanelTreeBranch>(child));

    //for (size_t i = 0; i < directories.size(); i++)
    //    SetupBranches(p_parent.get()->GetChildreens, path);
}

bool UI::ContentDrawerPanel::TryOpenFile(PanelTreeBranch& p_branch)
{
    std::string message = "Try to open file, path : " + p_branch.GetPathName();
    Core::EventManager::GetInstance().Invoke<EditorUI::DebugEvent>(message.c_str());

    //can display other items
    return false;
}

//ImFont& GetBigFont()
//{
//    static float FONT_SIZE = 100;
//
//    ImFont myFont = *ImGui::GetFont();
//    myFont.FontSize = FONT_SIZE;
//
//    return myFont;
//}

UI::PanelTreeBranch::PanelTreeBranch(const std::string& p_name, bool p_hideLeafs) :
    m_name(p_name), 
    m_forceState(EForceState::NOTHING),
	m_hideLeafs(p_hideLeafs),
    m_parent(nullptr),
    m_callback(nullptr)
{}

UI::PanelTreeBranch::PanelTreeBranch(const std::string& p_name, const Childreen& p_branches, bool p_hideLeafs) :
    m_name(p_name),
    m_forceState(EForceState::NOTHING),
    m_hideLeafs(p_hideLeafs),
    m_parent(nullptr),
    m_callback(nullptr)
{
    SetBranches(p_branches);
}

PanelTreeBranch::Childreen& UI::PanelTreeBranch::SetBranches(const Childreen& p_branches)
{
    m_childreen = p_branches;
    for (auto& child : p_branches)
        child.second->m_parent = this;

    return m_childreen;
}

PanelTreeBranch::Childreen& UI::PanelTreeBranch::SetBranches(const std::set<std::shared_ptr<PanelTreeBranch>>& p_branches)
{
    m_childreen.clear();
    for (auto& child : p_branches)
    {
        child->m_parent = this;
        m_childreen.insert({ child.get()->GetName(), child });
    }

    return m_childreen;
}

void UI::PanelTreeBranch::AddBranch(const std::shared_ptr<PanelTreeBranch>& p_branch)
{
    auto it = m_childreen.insert(m_childreen.end(), { p_branch.get()->GetName(), p_branch});
    it->second.get()->m_parent = this;
}

void UI::PanelTreeBranch::RemoveBranch(const std::string& p_name)
{
    for (auto it = m_childreen.begin(); it != m_childreen.end(); it++)
    {
        if (it->second.get()->m_name == p_name)
        {
            m_childreen.erase(it);
            break;
        }
    }
}

void UI::PanelTreeBranch::ForceOpenParents(bool p_openSelf)
{
    if (p_openSelf)
        m_forceState = EForceState::FORCE_OPEN;

    if (m_parent != nullptr)
        m_parent->ForceOpenParents(true);
}

void UI::PanelTreeBranch::ForceCloseChildreen(bool p_closeSelf)
{
    if (p_closeSelf)
        m_forceState = EForceState::FORCE_CLOSE;

    for (auto& child : m_childreen)
        child.second->ForceCloseChildreen(true);
}

void UI::PanelTreeBranch::ForceOpenAll()
{
    m_forceState = EForceState::FORCE_OPEN;

    for (auto& child : m_childreen)
        child.second->ForceOpenAll();
}

void UI::PanelTreeBranch::SetOnClickCallback(const std::shared_ptr<BranchCallback>& p_callback)
{
    m_callback = p_callback;
}

void UI::PanelTreeBranch::SetAllOnClickCallback(const std::shared_ptr<BranchCallback>& p_callback)
{
    m_callback = p_callback;

    for (auto& child : m_childreen)
        child.second->SetAllOnClickCallback(p_callback);
}

void UI::PanelTreeBranch::SetAllBranchesOnClickCallback(const std::shared_ptr<BranchCallback>& p_callback)
{
    if (IsBranch())
        m_callback = p_callback;

    for (auto& child : m_childreen)
        child.second->SetAllBranchesOnClickCallback(p_callback);
}

void UI::PanelTreeBranch::SetAllLeavesOnClickCallback(const std::shared_ptr<BranchCallback>& p_callback)
{
    if (!IsBranch())
        m_callback = p_callback; 

    for (auto& child : m_childreen)
        child.second->SetAllLeavesOnClickCallback(p_callback);
}

void UI::PanelTreeBranch::DisplayAndUpdatePanel()
{
    switch (m_forceState)
    {
    case UI::PanelTreeBranch::EForceState::FORCE_OPEN:
        ImGui::SetNextItemOpen(true, ImGuiCond_::ImGuiCond_Always);
        break;
    case UI::PanelTreeBranch::EForceState::FORCE_CLOSE:
        ForceCloseChildreen();
        ImGui::SetNextItemOpen(false, ImGuiCond_::ImGuiCond_Always);
        break;
    case UI::PanelTreeBranch::EForceState::NOTHING:
    default:
        break;
    }

    DisplayTreePanel();

    m_forceState = EForceState::NOTHING;
}

bool UI::PanelTreeBranch::DisplayAndUpdateSelection(float& p_width, float& /*p_height*/, bool p_doubleClicked)
{
    auto font = EditorUI::GetIconFont();
    auto cursorPos = ImGui::GetCursorPos();
    std::string iconTxt;

    if (IsBranch())
        iconTxt = "Fl";
    else
        iconTxt = "Tx";

    ImGui::PushFont(font);
    ImVec2 sz = ImGui::CalcTextSize(iconTxt.c_str());
    ImGui::PopFont();
    //float canvasWidth = ImGui::GetWindowContentRegionWidth();
    float canvasWidth = p_width - 16;
    float origScale = font->Scale;
    font->Scale = canvasWidth / sz.x;
    ImGui::SetCursorPos({cursorPos.x + 8, cursorPos.y + 8});

    ImGui::PushFont(font);
    ImGui::Text("%s", iconTxt.c_str());
    ImGui::PopFont();
    font->Scale = origScale;

    cursorPos = ImGui::GetCursorPos();
    ImGui::SetCursorPos({ cursorPos.x + 4, cursorPos.y + 4 });

    ImGui::PushTextWrapPos(p_width - 4);
    ImGui::TextWrapped(m_name.c_str());
    ImGui::PopTextWrapPos();


    if (p_doubleClicked && m_callback != nullptr)
        return (*m_callback)(*this);

    //can display other items
    return false;
}

const std::string& UI::PanelTreeBranch::GetName()
{
    return m_name;
}

void UI::PanelTreeBranch::DisplayTreePanel()
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick;
    flags |= IsBranch() ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Bullet;

    bool open = ImGui::TreeNodeEx(m_name.c_str(), flags);

    if (ImGui::GetMouseClickedCount(0) == 1 && ImGui::IsItemHovered() &&
        m_callback != nullptr)
        (*m_callback)(*this);

    if (open)
    {
        for (auto& node : m_childreen)
        {
            if (m_hideLeafs && node.second.get()->IsBranch())
                node.second->DisplayAndUpdatePanel();
        }

        ImGui::TreePop();
    }
}

bool UI::PanelTreeBranch::IsBranch() const
{
    return !m_childreen.empty();
}

const PanelTreeBranch::Childreen& UI::PanelTreeBranch::GetChildreen() const
{
    return m_childreen;
}

std::string UI::PanelTreeBranch::GetPathName() const
{
    std::vector<const PanelTreeBranch*> parents;
    parents.push_back(this);

    //get all parents
    while (parents.back()->m_parent != nullptr)
    {
        parents.push_back(parents.back()->m_parent);
    }

    std::string path;
    
    for (auto it = parents.rbegin(); it != parents.rend(); it++)
        path += (*it)->m_name + "$";

    return path;
}

void UI::PanelSelectionBox::SetSelectionSize(float p_width, float p_height)
{
    m_width = p_width;
    m_height = p_height;
}

void UI::PanelSelectionBox::DisplayAndUpdatePanel()
{
    static float spacingX = 10;
    static auto Padding = ImVec2(15, 15);
    ImGuiStyle& style = ImGui::GetStyle();
    float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

    ImGuiSelectableFlags    sFlags = ImGuiSelectableFlags_None;
    auto                    cFlags = ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysAutoResize;

    size_t count = m_elements.size();

    for (size_t i = 0; i < count; i++)
    {
        auto item = m_elements[i].get();
        bool isSelected = m_currentSelection.contains(item);
        auto isBreak = false; auto open = false;

        ImGui::BeginChild(std::string("##" + std::to_string(i)).c_str(), ImVec2(m_width + Padding.x, m_height + Padding.y), cFlags);

        auto cursorBefore = ImGui::GetCursorPos();
        ImGui::PushID(static_cast<int>(i));
        open = ImGui::Selectable("##", isSelected, sFlags, ImVec2(m_width, m_height));
        ImGui::PopID();
        auto cursorAfter = ImGui::GetCursorPos();

        bool doubleClicked = ImGui::GetMouseClickedCount(0) == 2 && ImGui::IsItemHovered();
        float last_button_x2 = ImGui::GetItemRectMax().x;
        float next_button_x2 = last_button_x2 + style.ItemSpacing.x + m_width; // Expected position if next button was on same line

        ImGui::SetCursorPos(cursorBefore);
        isBreak = item->DisplayAndUpdateSelection(m_width, m_height, doubleClicked);

        ImGui::EndChild();
        //ImGui::GetID();
        if (i + 1 < count && next_button_x2 < window_visible_x2)
        {
            ImGui::SameLine();
        }

        if (open)
        {
            if (isSelected)
                m_currentSelection.erase(item);
            else
                m_currentSelection.insert(item);
        }

        if (isBreak)
            break;
    }
}

void UI::PanelSelectionBox::SetSelectionBoxable(const std::vector<std::shared_ptr<ISelectionBoxable>>& p_elements)
{
    m_elements = p_elements;
}

void UI::PanelSelectionBox::DisplayCenteredText(const std::string& p_text, float p_maxWidth)
{
    //float win_width = ImGui::GetWindowSize().x;
    float text_width = ImGui::CalcTextSize(p_text.c_str()).x;

    // offset cursor
    auto cursorPos = ImGui::GetCursorPos();// (ImVec2(cursorPos.x + 10, cursorPos.y + 10));

    float text_indentation = (p_maxWidth - text_width) * 0.5f;

    // if iconTxt is too long to be drawn on one line, `text_indentation` can
    // become too small or even negative, so we check a minimum indentation
    float min_indentation = 0.0f;
    if (text_indentation <= min_indentation) {
        text_indentation = min_indentation;
    }

    ImGui::SameLine(text_indentation);
    ImGui::PushTextWrapPos(p_maxWidth - text_indentation);
    ImGui::TextWrapped(p_text.c_str());
    ImGui::PopTextWrapPos();
}
