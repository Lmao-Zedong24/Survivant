//UI.cpp

#include "SurvivantUI/UI.h"

#include "SurvivantApp/Windows/Window.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui_internal.h"


UI::EditorUI::EditorUI() : 
    m_main(std::make_shared<MainPanel>()),
    m_currentPanels()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Dockspace

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    //default panels here 
    m_currentPanels.insert(std::make_shared<TestPanel>("Test1"));
    m_currentPanels.insert(std::make_shared<TestPanel>("Test2"));
    m_currentPanels.insert(std::make_shared<TestPanel>("Test3"));
    m_currentPanels.insert(std::make_shared<TestPanel>("Test4"));

    MainPanel::ChangeLayout l = std::bind(&EditorUI::Layout1, this, std::placeholders::_1);
    m_main->ChangePanelLayout(l);

    //spawn save m_panel on event close request
    //Core::EventManager::GetInstance().AddListenner<App::Window::WindowCloseRequest>(
    //    App::Window::WindowCloseRequest::EventDelegate(std::bind(&EditorUI::CreateSavePanel, this)));
}

UI::EditorUI::~EditorUI()
{
}

void UI::EditorUI::InitEditorUi(App::Window* p_window)
{
    ImGui_ImplGlfw_InitForOpenGL(p_window->GetWindow(), true);
//#ifdef __EMSCRIPTEN__
//    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
//#endif
    ImGui_ImplOpenGL3_Init(App::GLSL_Version);
}

void UI::EditorUI::AddImageWindow(intptr_t p_textureId)
{
    static int i = 0;
    m_currentPanels.insert(std::make_shared<ImagePanel>(std::string("texture-") + std::to_string(i++), p_textureId));
}

void UI::EditorUI::StartFrameUpdate()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    Core::EventManager::GetInstance().Invoke<EditorUI::DebugEvent>("Created test panel");

    bool b = true;
    ImGui::ShowDemoWindow(&b);
}

void UI::EditorUI::RenderPanels()
{
    struct PanelFlags
    {
        std::shared_ptr<Panel> m_panel;
        Panel::ERenderFlags m_flags = Panel::ERenderFlags();
    };

    std::vector<PanelFlags> pfArray(m_currentPanels.size());

    {//main always first
        auto flags = m_main->Render();
        if (flags != Panel::ERenderFlags())
            pfArray.push_back({ m_main, flags });
    }

    for (auto& panel : m_currentPanels)
    {
        auto flags = panel->Render();
        if (flags != Panel::ERenderFlags())
            pfArray.push_back({ panel, flags });
    }

    //handle m_flags after
    for (auto& pf : pfArray)
        HandlePanelFlags(pf.m_panel, pf.m_flags);
}

void UI::EditorUI::EndFrameUpdate()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::EditorUI::HandlePanelFlags(std::shared_ptr<Panel> p_panel, Panel::ERenderFlags p_flags)
{
    if (p_flags & Panel::CLOSE)
        m_currentPanels.erase(p_panel);

    if (p_flags & Panel::ADD_TEST_PANNEL)
        CreateNewTestPanel();

    if (p_flags & Panel::ADD_CONSOLE_PANNEL)
        CreateConsolePanel();
}

void UI::EditorUI::CreateNewTestPanel()
{
    static int i = 0;

    m_currentPanels.insert(std::make_shared<TestPanel>(std::string("test-") + std::to_string(i++)));
}

void UI::EditorUI::CreateSavePanel()
{
    if (SavePanel::GetPanelCount() != 0)
        m_currentPanels.insert(std::make_shared<SavePanel>());
}

void UI::EditorUI::CreateConsolePanel()
{
    m_currentPanels.insert(std::make_shared<ConsolePanel>());
}

void UI::EditorUI::Layout1(int p_dockspaceId)
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiID id = p_dockspaceId;

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;


    ImGui::DockBuilderRemoveNode(id); // clear any previous layout
    ImGui::DockBuilderAddNode(id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(id, viewport->Size);

    auto dock_id_top = ImGui::DockBuilderSplitNode(p_dockspaceId, ImGuiDir_Up, 0.2f, nullptr, &id);
    auto dock_id_down = ImGui::DockBuilderSplitNode(id, ImGuiDir_Down, 0.25f, nullptr, &id);
    auto dock_id_left = ImGui::DockBuilderSplitNode(id, ImGuiDir_Left, 0.2f, nullptr, &id);
    auto dock_id_right = ImGui::DockBuilderSplitNode(id, ImGuiDir_Right, 0.15f, nullptr, &id);


    // we now dock our windows into the docking node we made above
    ImGui::DockBuilderDockWindow("texture-0", id);
    ImGui::DockBuilderDockWindow("Test1", dock_id_right);
    ImGui::DockBuilderDockWindow("Test2", dock_id_left);
    ImGui::DockBuilderDockWindow("Test3", dock_id_down);
    ImGui::DockBuilderDockWindow("Test4", dock_id_top);


    ImGui::DockBuilderFinish(id);
}
