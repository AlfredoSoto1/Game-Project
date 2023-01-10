#pragma once

#include "Gui/Cursor.h"

namespace Uranium {

	class Window;

	class Mouse {
	private:
		friend class Application;

		Cursor cursor;

		bool* mouseButtons;

		void update();

	public:
		Mouse(Window* _window);
		virtual ~Mouse();

		Cursor& getCursor();

		bool isButtonDown(int _button);

		int isMouseToggled(int _button);
	};
}