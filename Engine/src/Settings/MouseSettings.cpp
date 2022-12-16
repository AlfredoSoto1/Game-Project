#include "MouseSettings.h"

#include <GLFW/glfw3.h>

#include "Listener/MouseCallback.h"
#include "Display/Components/Window.h"

using namespace Settings;
using namespace Display;
using namespace Callback;

MouseSettings::MouseSettings(Window* _window) {
	xPosition = 0.0;
	yPosition = 0.0;

	xPositionNormalized = 0.0;
	yPositionNormalized = 0.0;

	yScroll = 0.0;
	xScroll = 0.0;

	callback = new MouseCallback(_window);
	mouseButtons = new bool[GLFW_MOUSE_BUTTON_LAST];
}

MouseSettings::~MouseSettings() {
	delete mouseButtons;
	delete callback;
}

Callback::MouseCallback& MouseSettings::getCallback() {
	return *callback;
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