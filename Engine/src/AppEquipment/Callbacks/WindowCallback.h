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
		WindowCallback(Application::App* _app);

	private:
		friend class Display::Window;
		friend class Application::App;
	};
}