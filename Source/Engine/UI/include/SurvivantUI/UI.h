//UI.h
#pragma once

#include "Panel.h"
#include "Menu.h"

#include "SurvivantCore/Events/Event.h"

#include <unordered_set>
#include <memory>

//foward declaration
struct ImFont;
namespace App
{
	class Window;
}

namespace UI
{
	class MainPanel;

	class IUI
	{
		virtual void StartFrameUpdate() = 0;
		virtual void EndFrameUpdate() = 0;
	};

	class EditorUI : public IUI
	{
	public:
		class DebugEvent : public Core::Event<const char*> {};

		EditorUI();
		~EditorUI(); 

		static ImFont* GetIconFont();

		void InitEditorUi(App::Window* p_window);

		void AddImageWindow(intptr_t p_textureId);

		void StartFrameUpdate() override;
		void RenderPanels();
		void EndFrameUpdate() override;

		void CreateNewTestPanel();
		void TryCreateSavePanel();
		void CreateSavePanel();
		void CreateConsolePanel();
		void CreateContentPanel();

		void Layout1(int p_dockspaceId);


	private:
		typedef void (UI::EditorUI::* EndFrameCallback)();

		MenuBar CreateMenuBar();
		void HandlePanelFlags(std::shared_ptr<Panel> p_id, Panel::ERenderFlags p_flags);

		static constexpr int ICON_FONT_SIZE = 200;
		static constexpr int DEFAULT_FONT_SIZE = 15;

		static inline ImFont* s_iconFont = nullptr;

		std::unordered_set<std::shared_ptr<Panel>>		m_currentPanels;
		std::shared_ptr<MainPanel>						m_main;
		std::vector<EndFrameCallback>					m_endFrameCallbacks;
	};
}
