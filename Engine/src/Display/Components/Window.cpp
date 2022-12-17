#include "Window.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Settings/MouseSettings.h"
#include "Settings/WindowSettings.h"

#include "Callbacks/MouseCallback.h"
#include "Callbacks/WindowCallback.h"

#include "Display/Graphics/SceneUtils/Stage.h"

using namespace std;
using namespace Display;
using namespace Settings;
using namespace Callback;
using namespace StageUtils;

Window::Window(const WindowSettings&& _settings) {
	this->hadStageCreated = false;
	this->stage = nullptr;
	this->winPtr = nullptr;
	this->mouseSettings = nullptr;
	this->mouseSettings = new MouseSettings();
	this->windowSettings = new WindowSettings(_settings);

	this->mouseCallback = nullptr;
	this->windowCallback = nullptr;
}

Window::Window(const string& _title, unsigned int _width, unsigned int _height) {
	this->hadStageCreated = false;
	this->stage = nullptr;
	this->winPtr = nullptr;
	this->mouseSettings = nullptr;
	this->mouseSettings = new MouseSettings();
	this->windowSettings = new WindowSettings();

	this->mouseCallback = nullptr;
	this->windowCallback = nullptr;

	this->windowSettings->setTitle(_title);
	this->windowSettings->setSize(_width, _height);
}

Window::~Window() {
	delete mouseSettings;
	delete windowSettings;
}

void Window::close() {
	if(winPtr) glfwSetWindowShouldClose(winPtr, GLFW_TRUE);
}

void Window::focus() {
	if(winPtr) glfwFocusWindow(winPtr);
}

void Window::attach(StageUtils::Stage* _stage) {
	this->stage = _stage;
}

StageUtils::Stage& Window::getStage() {
	return *stage;
}

WindowSettings& Window::getWindowSettings() {
	return *windowSettings;
}

MouseSettings& Window::getMouseSettings() {
	return *mouseSettings;
}

Callback::MouseCallback& Window::getMouseCallback() {
	return *mouseCallback;
}

Callback::WindowCallback& Window::getWindowCallback() {
	return *windowCallback;
}


//definition of error callback
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

//overloads
Window::operator GLFWwindow* () {
	return winPtr;
}

bool Window::initGLEW() {
	if (glewInit() != GLEW_OK) {
		cout << "Couldn't inititate GLEW correctly." << endl;
		return false;
	}
	else {
		cout << glGetString(GL_VERSION) << endl;
		return true;
	}
}

bool Window::initGLFW() {
	if (!glfwInit()) {
		cout << "GLFW couldn't initiated correctly." << endl;
		return false;
	}
	return true;
}

void Window::start() {
	//setting error callback
	glfwSetErrorCallback(&error_callback);

	//Initiates GLFW - returns false if it couldn't initiate
	if (!initGLFW()) return;

	windowSettings->loadHints();
	windowSettings->apply();

	winPtr = glfwCreateWindow(
		windowSettings->getWidth(), windowSettings->getHeight(),
		windowSettings->getTitle().c_str(),
		windowSettings->isFullScreen() ? windowSettings->getCurrentMonitor() : NULL, NULL);
	if (!winPtr) {
		cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
		return;
	}

	//set settings context and prefferences
	windowSettings->setContext(winPtr);
	windowSettings->centerWindow();

	//create Display context
	glfwMakeContextCurrent(winPtr);
	glfwShowWindow(winPtr);

	//Initiates GLEW - returns false if it couldn't initiate
	if (!initGLEW()) return;
	glViewport(0, 0, windowSettings->getWidth(), windowSettings->getHeight());

	//setup callbacks
	mouseCallback = new MouseCallback(this);
	windowCallback = new WindowCallback(this);

	runLoop();
}

void Window::runLoop() {

	hadStageCreated = stage != nullptr;
	if (!hadStageCreated)
		stage = new Stage();

	stage->init(windowSettings);
	while (!glfwWindowShouldClose(winPtr)) {
		stage->update();
		pollEvents(GL_FALSE);
	}
	finish();
}

void Window::pollEvents(int _isOnCallback) {
	if (windowSettings->hasResized())
		glViewport(0, 0, windowSettings->getWidth(), windowSettings->getHeight());

	stage->render();
	
	glfwSwapBuffers(winPtr);
	windowSettings->hasResized() = false;

	if (!_isOnCallback)
		glfwPollEvents();

	stage->postRender();
}

void Window::finish() {
	stage->dispose();

	if(!hadStageCreated)
		delete stage;

	delete mouseCallback;
	delete windowCallback;

	glfwDestroyWindow(winPtr);
	glfwTerminate();
}

