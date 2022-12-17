#pragma once

namespace Display {
	class Window;
}

namespace Callback {
	class WindowCallback {
	public:
		WindowCallback(Display::Window* window);
	};
}