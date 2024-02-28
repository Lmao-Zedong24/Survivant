//Panel.h
#pragma once

#include "IMenuable.h"
#include "IPanelable.h"
#include "Panel.h"
#include "Menu.h"

#include "SurvivantApp/Inputs/InputManager.h"


#include <string>
#include <functional>

namespace UI
{
	class MenuButton : public IMenuable
	{
	public:
		using KeyPair = std::pair<App::InputManager::KeyboardKeyType, App::InputManager::KeyCallback>;

		MenuButton(const std::string& p_name, const App::InputManager::KeyCallback& p_callback);
		MenuButton(
			const std::string& p_name, 
			const App::InputManager::KeyCallback& p_callback, 
			const App::InputManager::KeyboardKeyType& p_shortcut);
		~MenuButton()override = default;

		void DisplayAndUpdateMenu() override;

		void AddShortcut(const App::InputManager::KeyboardKeyType& p_shortcut);

	private:
		std::string						m_name;
		std::string						m_shortcut;
		App::InputManager::KeyCallback	m_callback;
	};


	class PanelButton : IPanelable
	{
	public:
		PanelButton(const std::string& p_name, const std::function<void()>& p_callback) :
			m_name(p_name), m_callback(p_callback) 
		{}
		~PanelButton() = default;

		void DisplayAndUpdatePanel()override;

	private:
		std::string	m_name;
		std::function<void()> m_callback;
	};

	class PanelButtonList : IPanelable
	{
	public:
		PanelButtonList() = default;
		~PanelButtonList() = default;

		void DisplayAndUpdatePanel()override;

		std::vector<PanelButton> m_buttons;
	};

	class ImagePanel : public Panel
	{ 
	public:
		ImagePanel(const std::string& p_name, intptr_t p_textureId) : Panel(p_name), m_textureId(p_textureId){}
		~ImagePanel() = default;

		ERenderFlags Render() override;

	private:
		intptr_t m_textureId;
	};

	class TestPanel : public Panel
	{
	public:
		TestPanel(const std::string& p_name) : Panel(p_name) {}
		~TestPanel() = default;

		ERenderFlags Render() override;
	};

	class MainPanel : public Panel
	{ 
	public:
		using ChangeLayout = std::function<void(int)>;

		MainPanel();
		~MainPanel() = default;

		ERenderFlags Render() override;

		void ChangePanelLayout(const ChangeLayout& p_layout);

	private:
		void SetupLayout(int p_dockspaceId);

		static constexpr char NAME[] = "Main";

		ChangeLayout		m_layout;
		MenuBar				m_menuBar;
	};

	class InspectorPanel : public Panel
	{
	public:
		InspectorPanel();
		~InspectorPanel();

		ERenderFlags Render() override;

		//void SetupGameObject();

	private:
		static constexpr char NAME[] = "Inspector";

		static inline int s_panelCount = 0;
	};

	class SavePanel : public Panel
	{
	public:
		SavePanel();
		~SavePanel(); 

		ERenderFlags Render() override;

	private:
		static constexpr char NAME[] = "Save";
		
		static inline int s_panelCount = 0;

		PanelButtonList m_options;
		bool			m_open = true;
	};

}
