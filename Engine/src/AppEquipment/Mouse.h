#pragma once

namespace Application {
	class App;
}

namespace Equipment {
	class Equipments;
}

namespace Settings {
	class MouseSettings;
}

namespace Listener {
	class MouseListener;
}

namespace Equipment {
	class Mouse {
	private:
		friend class Equipment::Equipments;

		Settings::MouseSettings* settings;
		Listener::MouseListener* listener;

		Listener::MouseListener* getListener();

		void initCallback(Application::App* _appRef);

		void update();

	public:
		Mouse(Application::App* _appRef);
		~Mouse();

		Settings::MouseSettings& getSettings();

		void setListener(Listener::MouseListener* _mouseListener);
	};
}