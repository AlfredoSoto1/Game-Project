#pragma once

#include "Application/AppComponent.h"

namespace Application {
	class App;
	class AppComponent;
}

namespace SceneUtils {
	class SceneManager;
}

namespace PeripheralsUtils {

	class Mouse;

	class Peripherals : public Application::AppComponent {
	private:
		friend class Application::App;
		friend class SceneUtils::SceneManager;
		friend class Application::AppComponent;

		Mouse* mouse;

	public:
		Peripherals();
		~Peripherals();

		Mouse& getMouse();

		void init();
		void dispose();
	};
}