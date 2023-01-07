#pragma once

namespace Uranium {
	class Device;
	class Application;
	class MouseSettings;
	class MouseListener;

	class Mouse {
	private:
		friend class Device;

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