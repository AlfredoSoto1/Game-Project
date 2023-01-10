#pragma once

struct GLFWcursor;

namespace Uranium {
	
	class Window;

	class Cursor {
	private:
		friend class Mouse;

		double xPosition;
		double yPosition;

		double lastXpos;
		double lastYpos;
		
		double xSpeed;
		double ySpeed;

		double xNorm;
		double yNorm;

		bool isActive;

		Window* window;

		Cursor(Window* _window);

		void changePosition(double _xPosition, double _yPosition);
		void changeNormPosition(double _xNorm, double _yNorm);

	public:
		virtual ~Cursor();

		Cursor(const Cursor&) = delete;
		Cursor(const Cursor&&) = delete;

		double getXPosition();
		double getYPosition();

		double getXSpeed();
		double getYSpeed();

		double getXNormPosition();
		double getYNormPosition();

		bool isMoving();

		void reset();
		void hide();
		void grab();
		void backToDefault();
		
		//void setImage(const Image& _image);
		GLFWcursor* createCursor(unsigned int cursorShape);
		void setPosition(double _xPosition, double _yPosition);
	};
}