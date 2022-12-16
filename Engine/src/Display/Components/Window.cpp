#include "Window.h"

#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Settings/MouseSettings.h"
#include "Listener/WindowListener.h"

#include "Settings/WindowSettings.h"
#include "Display/Graphics/SceneUtils/Stage.h"

using namespace std;
using namespace Display;
using namespace Settings;
using namespace Listener;
using namespace StageUtils;

Window::Window(const WindowSettings& _settings) {
	this->stage = nullptr;
	this->winPtr = nullptr;
	this->mouseSettings = nullptr;
	this->windowListener = nullptr;
	this->settings = new WindowSettings(_settings);
}

Window::Window(const string& _title, unsigned int _width, unsigned int _height) {
	this->stage = nullptr;
	this->winPtr = nullptr;
	this->mouseSettings = nullptr;
	this->windowListener = nullptr;
	this->settings = new WindowSettings();

	this->settings->setTitle(_title);
	this->settings->setSize(_width, _height);
}

Window::~Window() {
	delete settings;
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

WindowSettings& Window::getSettings() {
	return *settings;
}

MouseSettings& Window::getMouseSettings() {
	return *mouseSettings;
}

WindowListener& Window::getWindowListener() {
	return *windowListener;
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

	settings->loadHints();
	settings->apply();

	winPtr = glfwCreateWindow(settings->getWidth(), settings->getHeight(), settings->getTitle().c_str(), settings->isFullScreen() ? settings->getCurrentMonitor() : NULL, NULL);
	if (!winPtr) {
		cout << "Failed to create GLFW window." << endl;
		glfwTerminate();
		return;
	}

	//set settings context and prefferences
	settings->setContext(winPtr);
	settings->centerWindow();

	//create Display context
	glfwMakeContextCurrent(winPtr);
	glfwShowWindow(winPtr);

	//Initiates GLEW - returns false if it couldn't initiate
	if (!initGLEW()) return;
	glViewport(0, 0, settings->getWidth(), settings->getHeight());

	//setup listeners
	this->mouseSettings = new MouseSettings(this);
	this->windowListener = new WindowListener(this);

	//mouseListener

	runLoop();
}

void Window::runLoop() {

	hadStageCreated = stage != nullptr;
	if (!hadStageCreated)
		stage = new Stage();

	stage->init(settings);
	while (!glfwWindowShouldClose(winPtr)) {
		stage->update();
		pollEvents(GL_FALSE);
	}
	finish();
}

void Window::pollEvents(int _isOnCallback) {
	if (settings->hasResized())
		glViewport(0, 0, settings->getWidth(), settings->getHeight());

	stage->render();
	
	glfwSwapBuffers(winPtr);
	settings->hasResized() = false;

	if (!_isOnCallback)
		glfwPollEvents();

	stage->postRender();
}

void Window::finish() {
	stage->dispose();

	if(!hadStageCreated)
		delete stage;

	delete mouseSettings;
	delete windowListener;

	glfwDestroyWindow(winPtr);
	glfwTerminate();
}

