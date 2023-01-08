#pragma once

namespace Uranium {
	class Application;
	class MouseSettings;
	class MouseListener;

	class Mouse {
	private:
		friend Application;
		MouseSettings* settings;
		MouseListener* listener;

		void initCallback();

		void update();

	public:
		Mouse();
		~Mouse();

		MouseSettings& getSettings();

		void setListener(MouseListener* _mouseListener);
	};
}