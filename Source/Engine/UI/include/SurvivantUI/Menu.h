//Menu.h
#pragma once

#include "IMenuable.h"
#include "IPanelable.h"

#include <string>
#include <vector>
#include <memory>

namespace UI
{
	class Menu : public IPanelable, public IMenuable
	{
	public:
		Menu(std::string p_name) : m_name(p_name) {};
		~Menu() = default;
		Menu(Menu& p_other) = delete;
		Menu(Menu&& p_other)noexcept;

		void DisplayAndUpdatePanel() override;
		void DisplayAndUpdateMenu() override;

		std::vector<std::unique_ptr<IMenuable>> m_items;
	private:
		void DisplayAndUpdate();

		std::string m_name;
	};

	class MenuBar : public IPanelable
	{
	public:
		void DisplayAndUpdatePanel() override;

		std::vector<Menu> m_menus;
	};
}
