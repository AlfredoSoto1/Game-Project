#pragma once

namespace FrameworkEngine {
	class Application;
}

namespace Settings {
	class MouseSettings;
}

namespace Listener {
	class MouseListener;
}

namespace Peripherals {
	class Device;

	class Mouse {
	private:
		friend class Peripherals::Device;

		Settings::MouseSettings* settings;
		Listener::MouseListener* listener;

		void initCallback(FrameworkEngine::Application* _reference);

		void update();

	public:
		Mouse(FrameworkEngine::Application* _reference);
		~Mouse();

		Settings::MouseSettings& getSettings();

		void setListener(Listener::MouseListener* _mouseListener);
	};
}