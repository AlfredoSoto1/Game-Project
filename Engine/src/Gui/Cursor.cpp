#include <GLFW/glfw3.h>

#include "UraniumApi.h"

#include "Cursor.h"
#include "Gui/Window.h"

using namespace Uranium;

Cursor::Cursor(Window* _window) {
	xNorm = 0.0;
	yNorm = 0.0;

	xPosition = 0.0;
	yPosition = 0.0;

	xSpeed = 0.0;
	ySpeed = 0.0;

	isActive = false;

	window = _window;
}

Cursor::~Cursor() {

}

void Cursor::changePosition(double _xPosition, double _yPosition) {
	xPosition = _xPosition;
	yPosition = _yPosition;
}

void Cursor::changeNormPosition(double _xNorm, double _yNorm) {
	xNorm = _xNorm;
	yNorm = _yNorm;
}

double Cursor::getXPosition() {
	return xPosition;
}

double Cursor::getYPosition() {
	return yPosition;
}

double Cursor::getXSpeed() {
	xSpeed = lastXpos - xPosition;
	lastXpos = xPosition;
	return xSpeed;
}
double Cursor::getYSpeed() {
	ySpeed = lastYpos - yPosition;
	lastYpos = yPosition;
	return ySpeed;
}

double Cursor::getXNormPosition() {
	return xNorm;
}
double Cursor::getYNormPosition() {
	return yNorm;
}

bool Cursor::isMoving() {
	return xSpeed != 0 && ySpeed != 0 && isActive;
}

void Cursor::reset() {
	
}

GLFWcursor* Cursor::createCursor(unsigned int cursorShape) {
	switch (cursorShape) {
	case GLFW_IBEAM_CURSOR:
		return glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
	case GLFW_HAND_CURSOR:
		return glfwCreateStandardCursor(GLFW_HAND_CURSOR);
	case GLFW_CROSSHAIR_CURSOR:
		return glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	case GLFW_HRESIZE_CURSOR:
		return glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
	case GLFW_VRESIZE_CURSOR:
		return glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
	default:
		return glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
	}
}

void Cursor::hide() {
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Cursor::grab() {
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Cursor::backToDefault() {
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Cursor::setPosition(double _xPosition, double _yPosition) {
	xPosition = _xPosition;
	yPosition = _yPosition;
	glfwSetCursorPos(*window, _xPosition, _yPosition);
}
