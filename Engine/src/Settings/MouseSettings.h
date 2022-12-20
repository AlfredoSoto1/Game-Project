#pragma once

namespace Callback {
	class MouseCallback;
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

		const char** getDropPath();
		unsigned int getPathCount();

		void setDropPath(unsigned int _pathCount, const char** _paths);

	private:
		friend class Callback::MouseCallback;

		bool* mouseButtons;

		double xPosition;
		double yPosition;
		
		double xPositionNormalized;
		double yPositionNormalized;

		double yScroll;
		double xScroll;

		const char** paths;
		unsigned int pathCount;

		void setScrollOffset(double _xOffset, double _yOffset);
		void setMousePosition(double _xPosition, double _yPosition);
		void setMousePositionNormalized(double _xNormal, double _yNormal);

	};
}