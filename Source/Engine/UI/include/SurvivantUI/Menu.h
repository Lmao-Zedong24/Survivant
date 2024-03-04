//Menu.h
#pragma once

#include "IMenuable.h"
#include "IPanelable.h"

#include <string>
#include <vector>
#include <memory>

namespace UI
{
	class Menu : public IMenuable , public IPanelable
	{
	public:
		//unique name
		Menu(std::string p_name) : m_name(p_name) {};
		~Menu() = default;
		Menu(const Menu& p_other);
		Menu(Menu&& p_other) noexcept;
		Menu& operator=(const Menu& p_other);

		/// <summary>
		/// Deep copy
		/// </summary>
		/// <returns></returns>
		IMenuable* Clone() const override;

		void DisplayAndUpdateMenu() override;
		void DisplayAndUpdatePanel() override;

		void SetName(const std::string& p_name);

		std::vector<std::unique_ptr<IMenuable>> m_items;
	private:
		void DisplayAndUpdate();

		std::string m_name;
	};

	class MenuBar : public IPanelable
	{
	public:
		MenuBar() = default;
		~MenuBar() = default;
		MenuBar(const MenuBar& p_other) = default;
		MenuBar(MenuBar&& p_other) noexcept = default;
		
		MenuBar& operator=(const MenuBar&) = default;
		MenuBar& operator=(MenuBar&&) = default;

		void DisplayAndUpdatePanel() override;

		std::vector<Menu> m_menus;
	};
}
