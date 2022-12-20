#pragma once

namespace Application {
	class App;
}

namespace Display {
	class Window;
}

namespace Callback {
	class WindowCallback {
	public:
		WindowCallback(Display::Window* window);

	private:
		friend class Display::Window;
		friend class Application::App;
	};
}