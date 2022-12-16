#include "WindowSettings.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Settings;

WindowSettings::WindowSettings(const WindowSettings& settings) 
	:
	title			(settings.title),
	context			(settings.context),
	monitor			(settings.monitor),
	width			(settings.width),
	height			(settings.height),
	targetFrames	(settings.targetFrames),
	transparency	(settings.transparency),
	xPosition		(settings.xPosition),
	yPosition		(settings.yPosition),
	is_Visible		(settings.is_Visible),
	is_Resizable	(settings.is_Resizable),
	is_Decorated	(settings.is_Decorated),
	is_FullScreen	(settings.is_FullScreen),
	is_AlwaysOnTop	(settings.is_AlwaysOnTop),
	is_VSyncEnabled	(settings.is_VSyncEnabled),
	is_DynamicUpdate(settings.is_DynamicUpdate),
	has_Resized		(settings.has_Resized),
	hasInitialized	(settings.hasInitialized),
	is_Maximized	(settings.is_Maximized),
	is_Minimized	(settings.is_Minimized)
{
}

WindowSettings::WindowSettings() {
	reset();
}

WindowSettings::~WindowSettings() {
	
}

void WindowSettings::reset() {
	//Sets all flags to their default value
	has_Resized = false;
	hasInitialized = false;

	//Sets all settings to their default value
	setTitle("Window");
	setSize(MIN_WIDTH, MIN_HEIGHT);
	setTargetFPS(30);
	setPosition(0, 0);
	setTransparency(100);

	setCurrentMonitor(0);

	setVisible(true);
	setResizable(true);
	setDecorated(true);
	setFullScreen(false);
	setAlwaysOnTop(false);
	setVSyncEnabled(false);
	setDynamicUpdate(false);
}

void WindowSettings::uninit() {
	hasInitialized = false;
}

void WindowSettings::apply() {
	hasInitialized = true;
}

void WindowSettings::loadHints() {
	if (hasInitialized) return;

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
	if (!hasInitialized) return;
	
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
	if(hasInitialized) glfwRestoreWindow(context);
}

void WindowSettings::maximize() {
	is_Maximized = true;
	is_Minimized = false;
	if (hasInitialized) glfwMaximizeWindow(context);
}

void WindowSettings::minimize() {
	is_Minimized = true;
	is_Maximized = false;
	if (hasInitialized) glfwIconifyWindow(context);
}

void WindowSettings::requestAttention() {
	if (hasInitialized) glfwRequestWindowAttention(context);
}

void WindowSettings::setTitle(const std::string& _title) {
	this->title = _title;
	if (hasInitialized) glfwSetWindowTitle(context, title.c_str());
}

void WindowSettings::setSize(unsigned int _width, unsigned int _height) {
	this->width = _width;
	this->height = _height;
	has_Resized = true;
	if (hasInitialized) glfwSetWindowSize(context, width, height);
}

void WindowSettings::setTargetFPS(unsigned int _FPS) {
	this->targetFrames = _FPS;
}


void WindowSettings::setPosition(unsigned int _xPosition, unsigned int _yPosition) {
	this->xPosition = _xPosition;
	this->yPosition = _yPosition;
	if (hasInitialized) glfwSetWindowPos(context, xPosition, yPosition);
}

void WindowSettings::setTransparency(unsigned int _transparency) {
	this->transparency = _transparency;
	if (!hasInitialized) return;
	glfwSetWindowAttrib(context, GLFW_TRANSPARENT_FRAMEBUFFER, transparency < 100 ? GLFW_TRUE : GLFW_FALSE);
	glfwSetWindowOpacity(context, transparency / 1.0f);
}

void WindowSettings::setCurrentMonitor(GLFWmonitor* _currentMonitor) {
	this->monitor = _currentMonitor;
}


void WindowSettings::setVisible(bool _isVisible) {
	this->is_Visible = _isVisible;
	if (!hasInitialized) return;
	if (is_Visible)
		glfwShowWindow(context);
	else
		glfwHideWindow(context);
}

void WindowSettings::setResizable(bool _isResizable) {
	this->is_Resizable = _isResizable;
	if (hasInitialized) glfwSetWindowAttrib(context, GLFW_RESIZABLE, is_Resizable ? GLFW_TRUE : GLFW_FALSE);
}

void WindowSettings::setDecorated(bool _isDecorated) {
	this->is_Decorated = _isDecorated;
	if (hasInitialized) glfwSetWindowAttrib(context, GLFW_DECORATED, is_Decorated ? GLFW_TRUE : GLFW_FALSE);
}

void WindowSettings::setFullScreen(bool _isFullScreen) {
	this->is_FullScreen = _isFullScreen;
	if (!hasInitialized) return;

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
	if (hasInitialized) glfwSetWindowAttrib(context, GLFW_FLOATING, is_AlwaysOnTop ? GLFW_TRUE : GLFW_FALSE);
}

void WindowSettings::setVSyncEnabled(bool _isVSyncEnabled) {
	this->is_VSyncEnabled = _isVSyncEnabled;
}

void WindowSettings::setDynamicUpdate(bool _isDynamicUpdate) {
	this->is_DynamicUpdate = _isDynamicUpdate;
}

void WindowSettings::centerWindow() {
	if (is_Maximized) return;
	if (!hasInitialized) return;
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

unsigned int WindowSettings::getTargetFPS() {
	return targetFrames;
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

bool WindowSettings::isVSyncEnabled() {
	return is_VSyncEnabled;
}

bool WindowSettings::isDynamicUpdate() {
	return is_DynamicUpdate;
}

bool& WindowSettings::hasResized() {
	return has_Resized;
}

