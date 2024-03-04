//UI.h
#pragma once

#include "Panel.h"

#include "SurvivantCore/Events/Event.h"

#include <unordered_set>
#include <memory>

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

		void InitEditorUi(App::Window* p_window);

		void AddImageWindow(intptr_t p_textureId);

		void StartFrameUpdate() override;
		void RenderPanels();
		void EndFrameUpdate() override;

		void CreateNewTestPanel();
		void CreateSavePanel();
		void CreateConsolePanel();

		void Layout1(int p_dockspaceId);

	private:

		void HandlePanelFlags(std::shared_ptr<Panel> p_id, Panel::ERenderFlags p_flags);

		std::unordered_set<std::shared_ptr<Panel>> m_currentPanels;
		std::shared_ptr<MainPanel> m_main;
	};
}
