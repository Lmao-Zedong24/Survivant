//UI.h
#pragma once

namespace App
{
	class Window;
}

namespace UI
{
	class EditorUI
	{
	public:
		EditorUI();
		~EditorUI();

		void InitEditorUi(App::Window* p_window);

		void Update();

	private:

	};
}
