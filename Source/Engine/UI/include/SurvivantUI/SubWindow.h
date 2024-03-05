//Panel.h
#pragma once

#include "IMenuable.h"
#include "IPanelable.h"
#include "Panel.h"
#include "Menu.h"

#include "SurvivantApp/Inputs/InputManager.h"
#include "SurvivantUI/UI.h"

#include <ctime>
#include <functional>
#include <map>
#include <string>
#include <unordered_set>


//foward declaration
struct ImGuiInputTextCallbackData;
struct ImVec4;

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

		IMenuable* Clone() const override;

		void DisplayAndUpdateMenu() override;

		void AddShortcut(const App::InputManager::KeyboardKeyType& p_shortcut);

	private:
		std::string						m_name;
		std::string						m_shortcut;
		App::InputManager::KeyCallback	m_callback;
	};


	class MenuCheckBox : public IMenuable
	{
	public:
		MenuCheckBox(const std::string& p_name, bool& p_isChecked);
		~MenuCheckBox() = default;

		IMenuable* Clone() const override;
		void DisplayAndUpdateMenu() override;

	private:
		std::string		m_name;
		bool*			m_isCheked;
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

	class PanelTextInput : IPanelable
	{
	public:
		PanelTextInput(std::string p_name, std::function<void(PanelTextInput&)> p_callback);
		~PanelTextInput() = default;

		void DisplayAndUpdatePanel()override;
		void Clear();
		const std::string& GetText()const;

		static void ClearPanelText(PanelTextInput& p_panel);

	private:
		//static int TextPanelCallBack(ImGuiInputTextCallbackData* data);

		std::string								m_name;
		std::string								m_buffer;
		std::function<void(PanelTextInput&)>	m_callback;
	};


	class PanelTextBox : IPanelable
	{
	public:
		using FilterSet = std::unordered_set<std::string>;

		PanelTextBox() = default;
		~PanelTextBox() = default;

		void DisplayAndUpdatePanel()override;

		/// <summary>
		/// Set filters for the text box, optimized for same lenght filters
		/// </summary>
		/// <param name="p_filters">display strings that start with at least a filter</param>
		void SetFilters(const FilterSet& p_filters);
		void AddFilter(const std::string& p_filter);
		void RemoveFilter(const std::string& p_filter);

		/// <summary>
		/// Adds filter if dosent contain, remove it if contains
		/// </summary>
		/// <param name="p_filter"></param>
		void AddOrRemoveFilter(const std::string& p_filter);

		void AddItem(const std::shared_ptr<ITextable>& item, bool p_willScrollToBottom = false);
		void Clear();
		void Copy();

	private:
		bool IsFilteredItem(const ITextable* p_item);
		void UpdateFilteredItems();

		std::vector<std::shared_ptr<ITextable>>		m_items;
		std::vector<std::shared_ptr<ITextable>>		m_filteredItems;
		std::map<size_t, FilterSet>					m_filters;
		bool										m_scrollToBottom = false;
		bool										m_copy = false;
	};

	class PanelUniqueSelection : IPanelable
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="p_selectable">Displayed options</param>
		/// <param name="p_callback">callback with all selected flags as a parameter</param>
		PanelUniqueSelection(
			std::string p_name,
			std::vector<std::string> p_selectable, 
			std::function<void(int)> p_callback);
		~PanelUniqueSelection() = default;

		virtual void DisplayAndUpdatePanel();

	private:
		std::string					m_name;
		std::string					m_items;
		int							m_count;
		int							m_curentSelection;
		std::function<void(int)>	m_callback;
	};

	class PanelMultipleSelection : IPanelable
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="p_selectable">Displayed options</param>
		/// <param name="p_callback">callback with the new selected index as parameter</param>
		PanelMultipleSelection(
			std::string p_name,
			std::vector<std::string> p_selectable, 
			std::function<void(int)> p_callback);
		~PanelMultipleSelection() = default;

		virtual void DisplayAndUpdatePanel();

	private:
		std::string GetDisplayString();

		std::string					m_name;
		std::vector<std::string>	m_items;
		int							m_count;
		int							m_curentSelection;
		std::function<void(int)>	m_callback;
	};
	
	class PanelTreeBranch : public IPanelable
	{
	public:
		using BranchCallback = std::function<void(size_t)>;

		PanelTreeBranch(const std::string& p_name);
		PanelTreeBranch(const std::string& p_name, const std::vector<PanelTreeBranch>& p_branches);
		~PanelTreeBranch() = default;

		virtual void DisplayAndUpdatePanel();

		std::vector<PanelTreeBranch>&	SetBranches(const std::vector<PanelTreeBranch>& p_branches);
		void							AddBranch(const PanelTreeBranch& p_branch);
		void							RemoveBranch(const std::string& p_name);
		void							ForceOpenParents(bool p_openSelf = false);
		void							ForceCloseChildreen(bool p_closeSelf = false);
		void							SetOnClickCallback(const std::shared_ptr<BranchCallback>& m_callback, size_t p_callbackId);

	private:
		enum class EForceState
		{
			NOTHING,
			FORCE_OPEN,
			FORCE_CLOSE,
		};

		std::string								m_name;
		PanelTreeBranch*						m_parent;
		std::vector<PanelTreeBranch>			m_childreen;
		EForceState								m_forceOpen;
		bool									m_wasOpen;
		std::shared_ptr<BranchCallback>			m_callback;
		size_t									m_callbackId;
	};

	//if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
	//void IsSelected(bool p_isSelected);


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
		TestPanel(const std::string& p_name);
		~TestPanel() = default;

		ERenderFlags Render() override;

		PanelUniqueSelection								m_unique;
		PanelMultipleSelection								m_multiple;
		PanelTreeBranch										m_tree;
		std::shared_ptr<PanelTreeBranch::BranchCallback>	m_callback;
	};

	class MainPanel : public Panel
	{ 
	public:
		using ChangeLayout = std::function<void(int)>;

		MainPanel();
		MainPanel(MenuBar&& p_menuBar);
		~MainPanel() = default;

		ERenderFlags Render() override;

		void SetMenuBar(MenuBar&& p_menuBar);
		void ChangePanelLayout(const ChangeLayout& p_layout);

	private:
		void SetupLayout(int p_dockspaceId);

		static constexpr char NAME[] = "Main";

		ChangeLayout		m_layout;
		MenuBar				m_menuBar;
		Panel::ERenderFlags m_panelFlags;
	};

	class ConsolePanel : public Panel
	{
	public:
		enum class ELogType
		{
			DEFAULT_LOG	=	1 << 0,
			DEBUG_LOG =		1 << 1,
			WARNING_LOG =	1 << 2,
			ERROR_LOG =		1 << 3,
			//COMMAND_LOG	=	1 << 4
		};

		struct LogInfo
		{
			ELogType m_type;
			std::string m_message;
		};

		ConsolePanel();
		~ConsolePanel();

		ERenderFlags Render() override;

		void AddConsoleLog(const LogInfo& p_log);

	private:
		class LogText : public ITextable
		{
		public:
			LogText(const LogInfo& p_logInfo);
			~LogText() = default;

			void DisplayAndUpdatePanel()override;
			std::string GetString(size_t p_len = 0)const override;
			size_t GetLength()const override;

		private:
			static constexpr char SPACER[] = "";

			LogInfo m_logInfo;
			size_t m_length;
		};

		static std::string LogTypeToString(ELogType p_type);

		/// <summary>
		/// returns a color associated with the LogType, or nullptr if there are none
		/// </summary>
		/// <param name="p_type"></param>
		/// <param name="p_color">[out]</param>
		static void LogTypeColor(ELogType p_type, ImVec4* p_color);

		void TextInputCallback(PanelTextInput& p_textInput);

		static constexpr char NAME[] = "DebugLog";
		static inline int s_panelCount = 0;

		PanelTextInput							m_input;
		PanelTextBox							m_textBox;
		PanelButtonList							m_buttons;
		Menu									m_filterMenu;
		//cant use vector<bool> bcs not container
		std::vector<unsigned char>				m_currentFilters;
		EditorUI::DebugEvent::ListenerId		m_eventHandle;
	};

	class SavePanel : public Panel
	{
	public:
		SavePanel();
		~SavePanel(); 

		ERenderFlags Render() override;

		static int GetPanelCount() { return s_panelCount; };

	private:
		static constexpr char NAME[] = "Save";
		
		static inline int s_panelCount = 0;

		PanelButtonList m_options;
		bool			m_open = true;
	};

	class ContentDrawerPanel : public Panel
	{
		ContentDrawerPanel();
		~ContentDrawerPanel();

		ERenderFlags Render() override;

		static int GetPanelCount() { return s_panelCount; };

	private:
		static constexpr char NAME[] = "ContentDrawer";

		static inline int s_panelCount = 0;

		PanelButtonList m_options;
		bool			m_open = true;
	};
}
