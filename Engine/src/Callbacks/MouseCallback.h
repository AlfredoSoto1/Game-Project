#pragma once

namespace Display {
	class Window;
}

namespace Callback {
	class MouseCallback {
	public:
		MouseCallback(Display::Window* window);
	};
}