#pragma once

namespace Display {
	class Window;
}

namespace Listener {
	class WindowListener {
	public:
		WindowListener(Display::Window* window);
		~WindowListener();

	private:
		int(*closeListener)			(Display::Window* window)					= nullptr;
		int(*focusListener)			(Display::Window* window, int isFocused)	= nullptr;
		int(*iconifyListener)		(Display::Window* window, int isIconified)	= nullptr;
		int(*maximizeListener)		(Display::Window* window, int isMaximized)	= nullptr;
	};
}