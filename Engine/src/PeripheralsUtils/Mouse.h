#pragma once

namespace Application {
	class App;
}

namespace Settings {
	class MouseSettings;
}

namespace Callback {
	class MouseCallback;
}

namespace PeripheralsUtils {
	class Mouse {
	private:
		Settings::MouseSettings* settings;
		Callback::MouseCallback* callback;

	public:
		Mouse(Application::App* _appRef);
		~Mouse();

		Settings::MouseSettings& getSettings();
		Callback::MouseCallback& getCallback();
	};
}