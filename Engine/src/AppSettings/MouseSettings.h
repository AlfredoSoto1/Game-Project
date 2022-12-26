#pragma once

namespace Equipment {
	class Mouse;
}

namespace Settings {
	class MouseSettings {
	public:
		MouseSettings();
		~MouseSettings();

		double getX();
		double getY();

		double getXNormalized();
		double getYNormalized();

		double getXScroll();
		double getYScroll();

		bool* getButtons();

	private:
		friend class Equipment::Mouse;

		bool* mouseButtons;

		double xPosition;
		double yPosition;
		
		double xPositionNormalized;
		double yPositionNormalized;

		double yScroll;
		double xScroll;

		void setScrollOffset(double _xOffset, double _yOffset);
		void setMousePosition(double _xPosition, double _yPosition);
		void setMousePositionNormalized(double _xNormal, double _yNormal);

	};
}