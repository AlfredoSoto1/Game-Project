#pragma once

namespace Display {
	class Window;
}

namespace Callback {
	class MouseCallback;
}

namespace Settings {
	class MouseSettings {
	public:
		MouseSettings(Display::Window* _window);
		~MouseSettings();

		Callback::MouseCallback& getCallback();

		double getX();
		double getY();

		double getXNormalized();
		double getYNormalized();

		double getXScroll();
		double getYScroll();

		bool* getButtons();

		void setScrollOffset(double _xOffset, double _yOffset);
		void setMousePosition(double _xPosition, double _yPosition);
		void setMousePositionNormalized(double _xNormal, double _yNormal);

	private:
		bool* mouseButtons;

		double xPosition;
		double yPosition;
		
		double xPositionNormalized;
		double yPositionNormalized;

		double yScroll;
		double xScroll;

		Callback::MouseCallback* callback;
	};
}