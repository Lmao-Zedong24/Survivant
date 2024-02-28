//UI.h
#pragma once

#include "Panel.h"
#include "SubWindow.h"

#include <unordered_set>
#include <memory>

namespace App
{
	class Window;
}

namespace UI
{
	class IUI
	{
		virtual void StartFrameUpdate() = 0;
		virtual void EndFrameUpdate() = 0;
	};

	class EditorUI : public IUI
	{
	public:
		EditorUI();
		~EditorUI(); 

		void InitEditorUi(App::Window* p_window);

		void AddImageWindow(intptr_t p_textureId);

		void StartFrameUpdate() override;
		void RenderPanels();
		void EndFrameUpdate() override;

		void CreateNewTestPanel();
		void CreateSavePanel();

		void Layout1(int p_dockspaceId);

	private:
		void HandlePanelFlags(std::shared_ptr<Panel> p_panel, Panel::ERenderFlags p_flags);

		std::unordered_set<std::shared_ptr<Panel>> m_currentPanels;
		std::shared_ptr<MainPanel> m_main;
	};
}
