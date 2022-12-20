/*
	GLFW
*/
#include <GLFW/glfw3.h>

/*
	Settings
*/
#include "Settings/MouseSettings.h"

using namespace Settings;

MouseSettings::MouseSettings() {
	xPosition = 0.0;
	yPosition = 0.0;

	xPositionNormalized = 0.0;
	yPositionNormalized = 0.0;

	yScroll = 0.0;
	xScroll = 0.0;

	paths = nullptr;
	pathCount = 0;

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

const char** MouseSettings::getDropPath() {
	return paths;
}
unsigned int MouseSettings::getPathCount() {
	return pathCount;
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

void MouseSettings::setDropPath(unsigned int _pathCount, const char** _paths) {
	this->paths = _paths;
	this->pathCount = _pathCount;
}
