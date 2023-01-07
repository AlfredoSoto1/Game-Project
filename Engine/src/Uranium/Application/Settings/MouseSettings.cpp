#define UR_GLFW
#include "Engine.h"

#include "MouseSettings.h"
using namespace Uranium;

MouseSettings::MouseSettings() {
	currentMods = -1;
	currentButton = -1;

	xPosition = 0.0;
	yPosition = 0.0;

	xPositionNormalized = 0.0;
	yPositionNormalized = 0.0;

	yScroll = 0.0;
	xScroll = 0.0;

	mouseButtons = new bool[GLFW_MOUSE_BUTTON_LAST];
}

MouseSettings::~MouseSettings() {
	delete mouseButtons;
}

double MouseSettings::getX() {
	return xPosition;
}

double MouseSettings::getY() {
	return yPosition;
}

double MouseSettings::getXNormalized() {
	return xPositionNormalized;
}
double MouseSettings::getYNormalized() {
	return yPositionNormalized;
}

double MouseSettings::getXScroll() {
	return xScroll;
}
double MouseSettings::getYScroll() {
	return yScroll;
}
 
bool* MouseSettings::getButtons() {
	return mouseButtons;
}

void MouseSettings::setScrollOffset(double _xOffset, double _yOffset) {
	this->xScroll = _xOffset;
	this->yScroll = _yOffset;
}

void MouseSettings::setMousePosition(double x, double y) {
	this->xPosition = x;
	this->yPosition = y;
}

void MouseSettings::setMousePositionNormalized(double x, double y) {
	this->xPositionNormalized = x;
	this->yPositionNormalized = y;
}

bool MouseSettings::isButtonDown(int button) {
	if (button < 0)
		return false;
	return mouseButtons[button] ? true : false;
}
