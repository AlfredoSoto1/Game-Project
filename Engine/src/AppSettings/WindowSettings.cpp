/*
	GLFW
*/
#include <GLFW/glfw3.h>

/*
	Window Settings
*/
#include "AppSettings/WindowSettings.h"

using namespace Settings;

WindowSettings::WindowSettings() {
	reset();
}

WindowSettings::~WindowSettings() {
	
}

void WindowSettings::reset() {
	//Sets all flags to their default value
	has_Resized = false;

	//Sets all settings to their default value
	setTitle("Default Window");
	setSize(MIN_WIDTH, MIN_HEIGHT);
	setPosition(0, 0);
	setTransparency(100);

	setCurrentMonitor(0);

	setVisible(true);
	setResizable(true);
	setDecorated(true);
	setFullScreen(false);
	setAlwaysOnTop(false);

	setGLVersion(4, 6);
}

void WindowSettings::loadHints() {

	glfwDefaultWindowHints();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mayorGLVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorGLVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	//Prepare Window Hits before launch
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_VISIBLE,					is_Visible						? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_DECORATED,					is_Decorated					? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_FLOATING,					is_AlwaysOnTop					? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED,					is_Maximized && !is_Minimized	? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE,					is_Resizable					? GL_TRUE : GL_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER,	transparency < 100				? GL_TRUE : GL_FALSE);
	//glfwWindowHint(GLFW_CENTER_CURSOR,				is_CursorCentered				? GL_TRUE : GL_FALSE);

	setCurrentMonitor(glfwGetPrimaryMonitor());
}

void WindowSettings::setContext(GLFWwindow* _context) {
	this->context = _context;
	if (context == nullptr) return;
	
	if (is_Resizable)
		glfwSetWindowSizeLimits(context, MIN_WIDTH, MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
	if (is_Minimized)
		minimize();
	if (transparency < 100)
		setTransparency(transparency);
}

void WindowSettings::restore() {
	is_Maximized = false;
	is_Minimized = false;
	if(context) glfwRestoreWindow(context);
}

void WindowSettings::maximize() {
	is_Maximized = true;
	is_Minimized = false;
	if (context) glfwMaximizeWindow(context);
}

void WindowSettings::minimize() {
	is_Minimized = true;
	is_Maximized = false;
	if (context) glfwIconifyWindow(context);
}

void WindowSettings::setTitle(const std::string& _title) {
	this->title = _title;
	if (context) glfwSetWindowTitle(context, title.c_str());
}

void WindowSettings::setSize(unsigned int _width, unsigned int _height) {
	this->width = _width;
	this->height = _height;
	has_Resized = true;
	if (context) glfwSetWindowSize(context, width, height);
}


void WindowSettings::setPosition(unsigned int _xPosition, unsigned int _yPosition) {
	this->xPosition = _xPosition;
	this->yPosition = _yPosition;
	if (context) glfwSetWindowPos(context, xPosition, yPosition);
}

void WindowSettings::changeSize(unsigned int _width, unsigned int _height) {
	this->width = _width;
	this->height = _height;
	has_Resized = true;
}

void WindowSettings::changePosition(unsigned int _xPosition, unsigned int _yPosition) {
	this->xPosition = _xPosition;
	this->yPosition = _yPosition;
}

void WindowSettings::setTransparency(unsigned int _transparency) {
	this->transparency = _transparency;
	if (!context) return;
	glfwSetWindowAttrib(context, GLFW_TRANSPARENT_FRAMEBUFFER, transparency < 100 ? GLFW_TRUE : GLFW_FALSE);
	glfwSetWindowOpacity(context, transparency / 1.0f);
}

void WindowSettings::setCurrentMonitor(GLFWmonitor* _currentMonitor) {
	this->monitor = _currentMonitor;
}


void WindowSettings::setVisible(bool _isVisible) {
	this->is_Visible = _isVisible;
	if (!context) return;
	if (is_Visible)
		glfwShowWindow(context);
	else
		glfwHideWindow(context);
}

void WindowSettings::setResizable(bool _isResizable) {
	this->is_Resizable = _isResizable;
	if (context) glfwSetWindowAttrib(context, GLFW_RESIZABLE, is_Resizable ? GLFW_TRUE : GLFW_FALSE);
}

void WindowSettings::setDecorated(bool _isDecorated) {
	this->is_Decorated = _isDecorated;
	if (context) glfwSetWindowAttrib(context, GLFW_DECORATED, is_Decorated ? GLFW_TRUE : GLFW_FALSE);
}

void WindowSettings::setFullScreen(bool _isFullScreen) {
	this->is_FullScreen = _isFullScreen;
	if (!context) return;

	if (monitor == nullptr) return;

	if (is_FullScreen) {
		glfwGetWindowPos(context, &xPosition, &yPosition);
		glfwSetWindowMonitor(context, monitor, 0, 0, width, height, 0);//have to put monitor scale
	}
	else {
		glfwSetWindowMonitor(context, 0, xPosition, yPosition, width, height, 0);
	}
	has_Resized = true;
}

void WindowSettings::setAlwaysOnTop(bool _isAlwaysOnTop) {
	this->is_AlwaysOnTop = _isAlwaysOnTop;
	if (context) glfwSetWindowAttrib(context, GLFW_FLOATING, is_AlwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
}

void WindowSettings::setGLVersion(unsigned int mayor, unsigned int minor) {
	this->mayorGLVersion = mayor;
	this->minorGLVersion = minor;
}

void WindowSettings::centerWindow() {
	if (is_Maximized) return;
	if (!context) return;
	if (monitor == nullptr) return;

	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
	this->xPosition = (videoMode->width - this->width) / 2;
	this->yPosition = (videoMode->height - this->height) / 2;
	glfwSetWindowPos(context, xPosition, yPosition);
}


std::string WindowSettings::getTitle() {
	return title;
}

unsigned int WindowSettings::getWidth() {
	return width;
}

unsigned int WindowSettings::getHeight() {
	return height;
}

unsigned int WindowSettings::getTransparency() {
	return transparency;
}

GLFWmonitor* WindowSettings::getCurrentMonitor() {
	return monitor;
}

int WindowSettings::getXPosition() {
	return xPosition;
}

int WindowSettings::getYPosition() {
	return yPosition;
}

GLFWmonitor** WindowSettings::getAvailableMonitors() {
	int availableMonitorCount = 0;
	return glfwGetMonitors(&availableMonitorCount);
}


bool WindowSettings::isVisible() {
	return is_Visible;
}

bool WindowSettings::isDecorated() {
	return is_Decorated;
}

bool WindowSettings::isResizable() {
	return is_Resizable;
}

bool WindowSettings::isFullScreen() {
	return is_FullScreen;
}

bool WindowSettings::isAlwaysOnTop() {
	return is_AlwaysOnTop;
}

bool& WindowSettings::hasResized() {
	return has_Resized;
}

