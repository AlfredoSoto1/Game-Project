#pragma once

#include "Framework/AppManager/AppComponent.h"

namespace FrameworkEngine {
	class Application;
	class AppComponent;
}

namespace SceneUtils {
	class SceneManager;
}

namespace Peripherals {

	class Mouse;

	class Device : public FrameworkEngine::AppComponent {
	private:
		friend class SceneUtils::SceneManager;
		friend class FrameworkEngine::Application;
		friend class FrameworkEngine::AppComponent;

		Mouse* mouse;

		void init();
		void update();
		void dispose();

	public:
		Device(FrameworkEngine::Application* _reference);
		~Device();

		Mouse& getMouse();
	};
}