//Panel.h
#pragma once

#include <vector>
#include <string>

namespace UI
{
	class Panel
	{
	public:
		enum ERenderFlags
		{
			CLOSE =					1 << 0,
			//ADD_TEST_PANNEL =		1 << 1,
			//ADD_CONSOLE_PANNEL =	1 << 2,
		};

		const std::string& GetName();
		virtual ERenderFlags Render() = 0;

	protected:
		Panel() = default;
		Panel(const std::string& p_name);

		std::string GetUniqueName(const char p_name[], size_t p_count);
		std::string m_name;
	};
}
