#pragma once

namespace Uranium {
	
	class Mouse;
	
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

		bool isButtonDown(int button);

	private:
		friend class Mouse;

		bool* mouseButtons;

		int currentMods;
		int currentButton;

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