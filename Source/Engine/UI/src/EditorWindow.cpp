//EditorWindow.cpp

#include "SurvivantUI/EditorWindow.h"



UI::EditorWindow::EditorWindow() : App::Window()
{
	m_shouldClose = 0;
	m_ui = nullptr;

	Core::EventManager::GetInstance().AddListenner<App::Window::WindowClosing>(([this]() { m_shouldClose = true; }));
}

void UI::EditorWindow::StartRender()
{
	App::Window::StartRender();
	m_ui->StartFrameUpdate();
}

void UI::EditorWindow::RenderUI()
{
	m_ui->RenderPanels();
}

void UI::EditorWindow::EndRender()
{
	m_ui->EndFrameUpdate();
	App::Window::EndRender();
}

bool UI::EditorWindow::ShouldClose()
{
	//return Window::ShouldClose();
	return Window::ShouldClose() && m_shouldClose;
}

void UI::EditorWindow::SetupUI(EditorUI* p_ui)
{
	m_ui = p_ui;
	m_ui->InitEditorUi(this);
	p_ui->AddImageWindow(static_cast<intptr_t>(m_textureId));
}
