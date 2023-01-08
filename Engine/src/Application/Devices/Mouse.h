#pragma once

namespace Uranium {
	class Application;
	class MouseSettings;
	class MouseEventListener;

	class Mouse {
	private:
		friend Application;
		MouseSettings* settings;
		MouseEventListener* listener;

		void initCallback();

		void update();

	public:
		Mouse();
		~Mouse();

		MouseSettings& getSettings();

		void setListener(MouseEventListener* _mouseListener);
	};
}